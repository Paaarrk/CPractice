#pragma once

#define SLOT_NAME	_T("\\\\.\\mailslot\\mailbox")


int MailReceiver();

int PartAdder(int argc, TCHAR* argv[]);

int DuplicateHandleChildProcess(int argc, TCHAR* argv[]);