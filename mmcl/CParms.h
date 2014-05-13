#ifndef PARMS_H
#define PARMS_H

class CParms
{
public:
void Init(char *line);
void Init();
void Shutdown(void);
char *Check(char *key);
bool Check(char *key, char *value);
void Append(char *key, char *value = NULL);
bool Remove(char *key, size_t *plen = NULL);
char *Find(char *str, char *key, size_t len);
char *GetCommandLine(void);
bool Initialised();
private:
	char *g_pszCommandLine;
	
};

extern CParms Parms;
#endif