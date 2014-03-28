/*
	Copyright (C) 2014 CurlyMo

	This file is part of pilight.

    pilight is free software: you can redistribute it and/or modify it under the 
	terms of the GNU General Public License as published by the Free Software 
	Foundation, either version 3 of the License, or (at your option) any later 
	version.

    pilight is distributed in the hope that it will be useful, but WITHOUT ANY 
	WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR 
	A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with pilight. If not, see	<http://www.gnu.org/licenses/>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../pilight.h"
#include "../pilight/log.h"
#include "common.h"
#include "log.h"
#include "protocol.h"
#include "hardware.h"
#include "binary.h"
#include "gc.h"
#include "elro_ad.h"

/**
 * Creates as System message informing the daemon about a received or created message
 * 
 * systemCodeLOW : integer number, Left part of the 32 bit system code (actually the high part but first when read from the left)
 * systemCodeHIGH : integer number, High part of the 32 bit system code (actually the low part.. you get the picture)
 * unitcode : unit being adressed, integer number
 * state : either 2 (off) or 1 (on)
 * groupEnabled : if 1 this affects a whole group of devices
 * 
 */
void elroADCreateMessage(int systemcodeLOW, int systemcodeHIGH, int unitcode, int state, int groupEnabled) {
	elro_ad->message = json_mkobject();
	//aka address
	json_append_member(elro_ad->message, "systemcodeLow", json_mknumber(systemcodeLOW));
	json_append_member(elro_ad->message, "systemcodeHigh", json_mknumber(systemcodeHIGH));
	//toggle all or just one unit
	if(groupEnabled == 1) {
	    json_append_member(elro_ad->message, "group", json_mkstring("enabled"));
	} else {
	    json_append_member(elro_ad->message, "group", json_mkstring("disabled"));
	}
	//aka channel
	json_append_member(elro_ad->message, "unitcode", json_mknumber(unitcode));
	//aka command
	if(state == 1) {
		json_append_member(elro_ad->message, "state", json_mkstring("on"));
	}
	else if(state == 2) {
		json_append_member(elro_ad->message, "state", json_mkstring("off"));
	} else {
		json_append_member(elro_ad->message, "state", json_mkstring("UNKOWN"));
	}

}

/**
 * This is the main method when reading a received code
 * Decodes the received stream
 * 
 */
void elroADParseCode(void) {
	int chunkCounter = 0;
	//utilize the "code" field 
	//at this point the code field holds translated "0" and "1" codes from the received pulses
	//this means that we have to combine these ourselves into meaningful values in groups of 2
	int chunkedCode[58];
	
	
	for(chunkCounter = 0; chunkCounter < 58; chunkCounter +=1)
	{
		if(elro_ad->code[(chunkCounter)*2] != 0) {
			//these are always zero - this is not a valid code
			logprintf(LOG_INFO,"invalid code in elro_ad-first word not a low: %i",elro_ad->code[(chunkCounter)*2]);
			return;
		}
		chunkedCode[chunkCounter] = elro_ad->code[(chunkCounter*2)+1];
	}
	
	//chunked code now contains "groups of 2" codes for us to handle. 
	
	//int systemcode = binToDec(chunkedCode, 11, 28);
    	int systemcodeLOW = binToDec(chunkedCode, 11, 28);
	int systemcodeHIGH = binToDec(chunkedCode, 29, 42);
	int groupcode = binToDec(chunkedCode, 43, 46);
	int groupcode2 = binToDec(chunkedCode, 49, 50);
	int unitcode = binToDec(chunkedCode, 51, 56);
	int state = binToDec(chunkedCode, 47, 48);
	int groupRes = 0;

	if((groupcode == 13) && (groupcode2 == 2)) {
	    groupRes = 0;
	} else if((groupcode == 3) && (groupcode2 == 3)) {
	    groupRes = 1;
	} else {
		return;
	}  
	if((state <1) || (state >2)) return;	
	elroADCreateMessage(systemcodeLOW, systemcodeHIGH, unitcode, state, groupRes);
}

/**
 * Creates a number of "low" entries (302 302). Note that each entry requires 2 raw positions
 * so e-s should be a multiple of 2
 * s : start position in the raw code (inclusive)
 * e : end position in the raw code (inclusive)
 */
void elroADCreateLow(int s, int e) {
	int i;

	for(i=s;i<=e;i+=2) {
		elro_ad->raw[i]=(elro_ad->plslen->length);
		elro_ad->raw[i+1]=(elro_ad->plslen->length);
	}
}

/**
 * Creates a number of "high" entries (302 1028). Note that each entry requires 2 raw positions
 * so e-s should be a multiple of 2
 * s : start position in the raw code (inclusive)
 * e : end position in the raw code (inclusive)
 */
void elroADCreateHigh(int s, int e) {
	int i;

	for(i=s;i<=e;i+=2) {
		elro_ad->raw[i]=(elro_ad->plslen->length);
		elro_ad->raw[i+1]=(elro_ad->pulse*elro_ad->plslen->length);
	}
}

/**
 * This simply clears the full length of the code to be all "zeroes" (LOW entries)
 */
void elroADClearCode(void) {
	elroADCreateLow(0,116);
}

/**
 * Takes the passed numbers (low and high being the left and right portions of the system code respectively)
 * converts them into raw and inserts them into the raw code at the appropriate position
 *
 * systemcodeLOW : integer number, left part of the 32 bit system code
 * systemcodeHIGH : integer number, right part of the 32 bit system code
 */
void elroADCreateSystemCode(int systemcodeLOW, int systemcodeHIGH) {
	int binary[255];
	int length = 0;
	int i=0, x=0;

	length = decToBinRev(systemcodeLOW, binary);
	for(i=0;i<=length;i++) {
		if(binary[i]==1) {
			x=i*2;
			elroADCreateHigh(22+x, 22+x+1);
		}
	}
	
	length = decToBinRev(systemcodeHIGH, binary);
	for(i=0;i<=length;i++) {
		if(binary[i]==1) {
			x=i*2;
			elroADCreateHigh(58+x, 58+x+1);
		}
	}
}

/**
 * Takes the passed number converts it into raw and inserts it into the raw code at the appropriate position
 *
 * unitcode : integer number, id of the unit to control
 */
void elroADCreateUnitCode(int unitcode) {
	int binary[255];
	int length = 0;
	int i=0, x=0;

	length = decToBinRev(unitcode, binary);
	for(i=0;i<=length;i++) {
		if(binary[i]==1) {
			x=i*2;
			elroADCreateHigh(102+x, 102+x+1);
		}
	}
}

/**
 * Takes the passed number converts it into raw and inserts it into the raw code at the appropriate position
 *
 * state : integer number, state value to set. can be either 1 (on) or 2 (off) 
 */
void elroADCreateState(int state) {
	if(state == 1) {
		elroADCreateHigh(94, 95);
		elroADCreateLow(96, 97);
	}
	else {
    		elroADCreateLow(94, 95);
		elroADCreateHigh(96, 97);
	}
}

/** 
 * sets the first group code block to the appropriate raw values.
 * Fro grouped mode this is the equivalent to 1100, for non-grouped mode 1011 
 *
 * group : integer value, 1 means grouped enabled, 0 means disabled 
 */
void elroADCreateGroupCode(int group) {
    if(group == 1) {
	elroADCreateHigh(86,87);
	elroADCreateHigh(88,89);
	elroADCreateLow(90,91);
	elroADCreateLow(92,93);
    } else {
	elroADCreateHigh(86,87);
	elroADCreateLow(88,89);
	elroADCreateHigh(90,91);
	elroADCreateHigh(92,93);
    }
}


/**
 * sets the second group code block to the appropriate raw values.
 * For Grouped Mode this is 11, for non grouped mode 01 
 *
 * group : integer value, 1 means grouped enabled, 0 means disabled 
 */
void elroADCreateGroupCode2(int group) {
    if(group == 1) {
	elroADCreateHigh(98,99);
	elroADCreateHigh(100,101);
    } else {
	elroADCreateLow(98,99);
	elroADCreateHigh(100,101);
    }
}


/** 
 * Inserts the (as far as is known) fixed message preamble
 * First eleven words are the preamble
 */
void elroADCreatePreamble(void) {
    elroADCreateHigh(0,1);
	elroADCreateHigh(2,3);
	elroADCreateLow(4,5);
	elroADCreateLow(6,7);
	elroADCreateLow(8,9);
	elroADCreateHigh(10,11);
	elroADCreateHigh(12,13);
	elroADCreateHigh(14,15);
	elroADCreateHigh(16,17);
	elroADCreateLow(18,19);
	elroADCreateLow(20,21);
}

/**
 * Inserts the message trailer (one HIGH) into the raw message 
 */
void elroADCreateFooter(void) {
	elro_ad->raw[114]=(elro_ad->plslen->length);
	elro_ad->raw[115]=(PULSE_DIV*elro_ad->plslen->length);
}


/**
 * Main method for creating a message based on daemon-passed values in the elro_ad protocol.
 * code : JSON Message containing the received parameters to use for message creation
 * 
 * returns : EXIT_SUCCESS or EXIT_FAILURE on obvious occasions
 */
int elroADCreateCode(JsonNode *code) {
	int systemcodeLOW = -1;
	int systemcodeHIGH = -1;
	int unitcode = -1;
	int group = -1;
	int state = -1;
	int tmp;

	json_find_number(code, "systemcodeLow", &systemcodeLOW);
	json_find_number(code, "systemcodeHigh", &systemcodeHIGH);
	
	json_find_number(code, "group", &group);
	json_find_number(code, "unitcode", &unitcode);
	
	if(json_find_number(code, "group", &tmp) == 0) {
	    group=1;
	} else {
	    group=0;
	}

	//on the reference remote, group toggles always used a unit code of 56.
        //for that reason we are enforcing that here
	if(group == 1) {
		unitcode = 56;	
	}

	if(json_find_number(code, "off", &tmp) == 0)
		state=2;
	else if(json_find_number(code, "on", &tmp) == 0)
		state=1;

	if(systemcodeLOW == -1 || systemcodeHIGH == -1 || unitcode == -1 || state == -1) {
		logprintf(LOG_ERR, "elro_ad: insufficient number of arguments");
		return EXIT_FAILURE;
	} else {
		elroADCreateMessage(systemcodeLOW, systemcodeHIGH, unitcode, state, group);
		elroADClearCode();
		elroADCreatePreamble();
		elroADCreateSystemCode(systemcodeLOW, systemcodeHIGH);
		elroADCreateGroupCode(group);
		elroADCreateState(state);
		elroADCreateGroupCode2(group);
		elroADCreateUnitCode(unitcode);
		elroADCreateFooter();
	}
	return EXIT_SUCCESS;
}

/**
 * Outputs help messages directly to the current output target (probably the console)
 */
void elroADPrintHelp(void) {
	printf("\t -s --systemcodeLow=systemcode\tcontrol a device with this systemcode (low part)\n");
	printf("\t -h --systemcodeLow=systemcode\tcontrol a device with this systemcode (high part)\n");
	printf("\t -g --group=group mode\ttoggle switching all devices on or off\n");
	printf("\t -u --unitcode=unitcode\t\tcontrol a device with this unitcode\n");
	printf("\t -t --on\t\t\tsend an on signal\n");
	printf("\t -f --off\t\t\tsend an off signal\n");
}

/**
 * Main Init method called to init the protocol and register its functions with pilight
 */ 
void elroADInit(void) {

	protocol_register(&elro_ad);
	protocol_set_id(elro_ad, "elro_ad");
	protocol_device_add(elro_ad, "elro_ad", "Elro Home Easy Advanced Switches (HE300)");
	protocol_plslen_add(elro_ad, 302);
	elro_ad->devtype = SWITCH;
	elro_ad->hwtype = RF433;
	elro_ad->pulse = 4;
	elro_ad->rawlen = 116;

	options_add(&elro_ad->options, 's', "systemcodeLow", has_value, config_id, "^(3[012]?|[012][0-9]|[0-9]{1})$");
	options_add(&elro_ad->options, 'h', "systemcodeHigh", has_value, config_id, "^(3[012]?|[012][0-9]|[0-9]{1})$");
	options_add(&elro_ad->options, 'g', "group", no_value, config_state, NULL);
	options_add(&elro_ad->options, 'u', "unitcode", has_value, config_id, "^(3[012]?|[012][0-9]|[0-9]{1})$");
	options_add(&elro_ad->options, 't', "on", no_value, config_state, NULL);
	options_add(&elro_ad->options, 'f', "off", no_value, config_state, NULL);

	protocol_setting_add_string(elro_ad, "states", "on,off");	
	protocol_setting_add_number(elro_ad, "readonly", 0);
	
	elro_ad->parseCode=&elroADParseCode;
	elro_ad->createCode=&elroADCreateCode;
	elro_ad->printHelp=&elroADPrintHelp;
}
