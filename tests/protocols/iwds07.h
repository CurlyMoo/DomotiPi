/*
  Copyright (C) 2019 by mwka

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

static const int iwds07_nrtests = 6;
static const struct raw_t iwds07_tests[] = {
	{
		"1230 410 410 1230 1640 410 410 1230 1640 410 1640 410 1640 410 410 1230 1230 410 410 1230 410 1230 410 1230 410 1230 410 1230 1230 410 1230 410 410 1230 410 1230 410 1230 410 1230 1230 410 410 1230 1230 410 410 1230 410 13940",
		"{\"unit\":49525,\"battery\":1,\"state\":\"opened\"}",
		NULL,
		0
	},
	{
		"1245 415 415 1245 1245 415 415 1245 1245 415 1660 415 1245 415 415 1245 1245 415 415 1245 415 1245 415 1245 415 1245 415 1245 1245 415 1245 415 415 1245 415 1245 415 1245 415 1245 1245 415 1245 415 1245 415 415 1245 415 14110",
		"{\"unit\":49525,\"battery\":1,\"state\":\"closed\"}",
		NULL,
		0
	},
	{
		"1233 411 411 1233 1233 411 1233 411 822 1233 1233 411 411 1233 411 1233 411 1233 1233 411 1233 411 1233 411 411 1233 411 1233 1233 411 1233 411 411 1233 411 1233 411 1233 411 1233 1233 411 411 1233 1233 411 411 1233 411 13974",
		"{\"unit\":52781,\"battery\":1,\"state\":\"opened\"}",
		NULL,
		0
	},
	{
		"1239 413 413 1239 1239 413 1239 413 413 1239 1239 413 413 1239 413 1239 413 1239 1239 413 1239 413 1239 413 413 1239 413 1239 1239 413 1239 413 413 1239 413 1239 413 1239 413 1239 1239 413 1239 413 1239 413 413 1239 413 14042",
		"{\"unit\":52781,\"battery\":1,\"state\":\"closed\"}",
		NULL,
		0
	},
	{
		"1236 412 412 1236 1236 412 1236 412 412 1236 1236 412 412 1236 1236 412 1236 412 1236 412 412 1236 412 1236 412 1236 1236 412 1236 412 1236 412 412 1236 412 1236 412 1236 412 1236 1236 412 412 1236 1236 412 412 1236 412 14008",
        "{\"unit\":58285,\"battery\":1,\"state\":\"opened\"}",
		NULL,
		0
	}
	{
		"1242 414 414 1242 1242 414 1242 414 414 1242 1242 414 414 1656 1242 414 1242 414 1242 414 414 1242 414 1242 414 1242 1242 414 1242 414 1242 414 414 1242 414 1242 414 1242 414 1242 1242 414 1242 414 1242 414 414 1242 414 14076",
        "{\"unit\":58285,\"battery\":1,\"state\":\"closed\"}",
		NULL,
		0
	}
};