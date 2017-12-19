#include <stdio.h>
#include <time.h>
int main() {
time_t now;
struct tm *t;
now=time(NULL);
t=localtime(&now);
printf("Son las %02d:%02d:%02d del %d/%d/%d\n",
t->tm_hour, t->tm_min, t->tm_sec,
t->tm_mon+1, t->tm_mday, t->tm_year+1900);
printf("Dia de la semana: %d\n", t->tm_wday+1);
printf("Dia del anno: %d\n", t->tm_yday+1);
printf(t->tm_isdst>0?"Horario de Verano\n":"Horario Normal\n");
return 0;
}