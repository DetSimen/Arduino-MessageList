#pragma once

// system messages

#define  msg_Empty 0x00
#define  msg_Error 0x01
#define  msg_Paint 0x02

// user messages

#define  msg_SecondTick			0x10
#define  msg_PrintRelayState	0x11
#define	 msg_ReadMQ2			0x12	//читать данные с датчика MQ2
#define  msg_MQ2Changed			0x13	// показания c MQ2 изменились
#define  msg_ReadKey			0x14

#define  msg_KeyDown			0x20	// кнопка нажата
#define	 msg_KeyUp				0x21	// кнопка отпущена

#define msg_VentON				0x22	// включить вытяжку
#define msg_VentOFF				0x23	// выключить вытяжку


