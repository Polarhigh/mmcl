#include "stdafx.h"
#include "CParms.h"
CParms Parms;

void CParms::Init()
{
	g_pszCommandLine=GetCommandLineA();
}

void CParms::Init(char *line)
{
	g_pszCommandLine = strdup(line);
}

void CParms::Shutdown(void)
{
	free(g_pszCommandLine);
}

char *CParms::Check(char *key)
{
	static char value[128] = "";
	char *str = strchr(g_pszCommandLine, *key);

	if (!str)
		return NULL;

	size_t len = strlen(key);
	str = this->Find(str, key, len);

	if (!str)
		return NULL;

	str += len;

	while (*str && *str == ' ')
		str++;

	if (*str && *str != '+' && *str != '-')
	{
		unsigned pos = 1;
		value[0] = *str++;

		while (*str && *str != ' ')
			value[pos++] = *str++;

		value[pos] = '\0';
	}

	return value;
}

bool CParms::Check(char *key, char *value)
{
	char *str = this->Check(key);

	if (!str)
		return false;

	strcpy(value, str);
	return true;
}

void CParms::Append(char *key, char *value)
{
	size_t cmdlen = strlen(g_pszCommandLine);
	size_t keylen = strlen(key);

	this->Remove(key, &keylen);
	g_pszCommandLine = (char *)realloc(g_pszCommandLine, cmdlen + 1 + keylen + 1 + (value ? strlen(value) + 1 : 1));

	char *buf = g_pszCommandLine + cmdlen;

	if (cmdlen)
		*buf++ = ' ';

	strcpy(buf, key);

	if (value)
	{
		buf += keylen;
		*buf++ = ' ';
		strcpy(buf, value);
	}
}

bool CParms::Remove(char *key, size_t *plen)
{
	char *str = strchr(g_pszCommandLine, *key);

	if (!str)
		return false;

	size_t len = plen ? *plen : strlen(key);
	str = this->Find(str, key, len);

	if (!str)
		return false;

	do
	{
		char *buf = str + len;

		while (*buf && *buf == ' ')
			buf++;

		if (*buf && *buf != '+' && *buf != '-')
		{
			do buf++;
			while (*buf && *buf != ' ');
		}

		strcpy(str, buf);

		if (!*str)
		{
			str--;

			while (str >= g_pszCommandLine && *str == ' ')
				*str-- = '\0';

			return true;
		}
	}
	while (str = this->Find(str, key, len));
	return true;
}

char *CParms::Find(char *str, char *key, size_t len)
{
	while (str = strchr(str, *key))
	{
		if (strncmp(str + 1, key + 1, len - 1))
		{
			str++;
			continue;
		}

		char *buf = str + len;

		if (!*buf || *buf == ' ')
			return str;

		str += len + 1;
	}

	return NULL;
}

char *CParms::GetCommandLine(void)
{
	return g_pszCommandLine;
}

bool CParms::Initialised()
{
	return !!g_pszCommandLine;
}