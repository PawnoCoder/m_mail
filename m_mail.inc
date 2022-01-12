/*

	About: Mail include v2.2
	Author: Noname

*/

#if !defined _samp_included
	#error "Please include a_samp or a_npc before m_mail"
#endif

#if !defined HTTP_ERROR_MALFORMED_RESPONSE
	#error "You must have a_http include in order to use this one."
#endif

#if defined _m_mail_included_
	#endinput
#endif
#define _m_mail_included_

/*
	Define const
*/

#if !defined M_MAIL_URL
	#error Please define the URL of the mail script. Example: #define M_MAIL_URL "example.com/m_mail.php"
#endif

#if !defined M_MAIL_ADDRESS
	#error Please define E-Mail address to send messages. Example: #define M_MAIL_ADDRESS "mymail@example.com"
#endif

#if !defined MAIL_TYPE_NORMAL
	#define MAIL_TYPE_NORMAL 0
#endif

#if !defined MAIL_TYPE_HTML
	#define MAIL_TYPE_HTML 1
#endif

#if !defined MAX_FUNCTION_NAME
	#define MAX_FUNCTION_NAME 32
#endif

#if !defined MAX_PLAYER_MAIL
	#define MAX_PLAYER_MAIL 64
#endif

#if !defined MAX_MAIL_SIZE
	#define MAX_MAIL_SIZE 512
#endif

/*
	Natives
*/

native __m_mail__HTTP(index, type, const url[], const data[], const callback[]) = HTTP;

/*
	Define functions
*/

#define Mail_Create:%0(%1) \
	forward MC_%0(%1); \
	public MC_%0(%1)

#define Mail_Show::%0(%1) \
	MC_%0(%1)

#define Mail_Response:%0(%1) \
	forward MR_%0(%1); \
	public MR_%0(%1)

#define Mail: #

#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

/*
	Forwards
*/

forward OnPlayerMailScriptResponse(playerid, response_code, const data[]);

/*
	Vars
*/

static
	m_player_function[MAX_PLAYERS][MAX_FUNCTION_NAME + 1 char];

/*
	Mail_Send
*/

stock Mail_Send(playerid, const function[], const to[], const additional_headers[], const subject[], const message[], type = MAIL_TYPE_NORMAL)
{
	new
		info[MAX_MAIL_SIZE + 1];

	m_player_function[playerid] = !"MR_";
	strcat(m_player_function[playerid], function);
	format(info, sizeof(info), "to=%s&additional_headers=%s&subject=%s&message=%s&additional_parameters="M_MAIL_ADDRESS"&type=%i", to, additional_headers, subject, message, type);
	__m_mail__HTTP(playerid, HTTP_POST, M_MAIL_URL, info, !"OnPlayerMailScriptResponse");
	return 1;
}

/*
	OnPlayerMailScriptResponse
*/

public OnPlayerMailScriptResponse(playerid, response_code, const data[])
{
	if (funcidx(m_player_function[playerid]) != -1)
		CallLocalFunction(m_player_function[playerid], !"iis", playerid, response_code, (isnull(data)) ? (!"\1") : (data));
	return 1;
}