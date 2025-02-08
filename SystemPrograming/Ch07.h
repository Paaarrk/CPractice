#ifndef __CH07_H__
#define __CH07_H__

#define	SLOT_NAME	_T("\\\\.\\mailslot\\mailbox")

int MailSender();

int NonStopAdderManager();

int MailSenderWithChild();

int MailSenderChild();

int DuplicateHandle();

#endif
