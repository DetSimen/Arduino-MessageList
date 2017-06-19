#pragma once

// сообщения, выделенные под системные

#define  msg_Empty 0x00
#define  msg_Error 0x01
#define  msg_Paint 0x02

// сообщения пользователя, даны только для примера, создавайте свои с номерами 0x10-0xFF
// удобно группировать сообщения по группам

// группа разное. 

#define  msg_SecondTick			  0x10    // пришел секундный тик
#define	 msg_ReadMQ2			    0x12	  // читать данные с датчика MQ2
#define  msg_MQ2Changed			  0x13	  // показания c MQ2 изменились

// группа клавиатуры

#define  msg_ReadKey			    0x20    // прочитать кнопку с клавы
#define  msg_KeyDown			    0x21	  // кнопка нажата
#define	 msg_KeyUp				    0x22	  // кнопка отпущена

// группа сообщений исполнительных устройств

#define msg_VentON				    0x82	  // включить вытяжку
#define msg_VentOFF				    0x83	  // выключить вытяжку


