#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
*/
#include <winsock2.h>
#define close closesocket
#define fork() 0
#define sleep(x) Sleep(x * 1000)

int fd;

void xyz(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args);
    char *s = (char *) malloc(len + 1);
    if(s != NULL) {
        vsprintf(s, fmt, args);
        send(fd, s, len, 0);
    }
    va_end(args);
}

char *line()
{
    static char buf[512] = {0}; static int offset = 0, len = 0;

    // remove last message
    memcpy(buf, buf + offset, len - offset);
    offset = len - offset, len = 0;

    int first = 1;

    while (1) {
        if(first == 0) {
            len = recv(fd, buf + offset, sizeof(buf) - offset, 0);
            if(len < 1) exit(0);
        }

        first = 0;

        char *x = memchr(buf, '\n', offset + len);
        if(x == NULL && offset + len == sizeof(buf)) {
            xyz("Command is too long\n");
            offset = 0;
            continue;
        }
        else if(x == NULL) {
            offset += len;
            continue;
        }

        char *y = memchr(buf, '\r', offset + len);
        if(y != NULL && y + 1 == x) {
            *y = 0;
        }

        return len += offset, *x = 0, offset = x - buf + 1, buf;
    }
}

void a_cups()
{
    xyz("       .._,,-~’’’¯¯¯’’~-,,\r\n"
"      ..,-‘’ ; ; ;_,,---,,_ ; ;’’-,           .._,,,---,,_\r\n"
"      .,’ ; ; ;,-‘ , , , , , ‘-, ; ;’-,,,,---~~’’’’’’~--,,,_ ..,,-~’’ ; ; ; ;__;’-,\r\n"
"      .| ; ; ;,’ , , , _,,-~’’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ¯’’~’-,,_ ,,-~’’ , , ‘, ;’,\r\n"
"      .’, ; ; ‘-, ,-~’’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;’’-, , , , , ,’ ; |\r\n"
"       ’, ; ;,’’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;’-, , ,-‘ ;,-‘\r\n"
"       .,’-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;’’-‘ ;,,-‘\r\n"
"      ..,’ ; ; ; ; ; ; ; ; ; ; ; ;__ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ‘-,’\r\n"
"      ,-‘ ; ; ; ; ; ; ; ; ; ;,-‘’¯: : ’’-, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; _ ; ; ; ; ;’,\r\n"
"     ..,’ ; ; ; ; ; ; ; ; ; ; ;| : : : : : :| ; ; ; ; ; ; ; ; ; ; ; ; ,-‘’¯: ¯’’-, ; ; ;’,\r\n"
"     .,’ ; ; ; ; ; ; ; ; ; ; ; ‘-,_: : _,-‘ ; ; ; ; ; ; ; ; ; ; ; ; | : : : : : :| ; ; ; |\r\n"
"     ,’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ¯¯ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;’-,,_ : :,-‘ ; ; ; ;|\r\n"
"    ..,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ,,-~’’ , , , , ,,,-~~-, , , , _ ; ; ;¯¯ ; ; ; ; ;|\r\n"
"..    ,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,’ , , , , , , ,( : : : : :) , , , ,’’-, ; ; ; ; ; ; ; ;|\r\n"
"   .,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;’, , , , , , , , ,’~---~’’ , , , , , ,’ ; ; ; ; ; ; ; ;’,\r\n"
"  .,-‘’ ; _, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ‘’~-,,,,--~~’’’¯’’’~-,,_ , ,_,-‘ ; ; ; ; ; ; ; ; ; ‘,\r\n"
"  ,-‘’-~’’,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; | ; ; | . . . . . . ,’; ,’’¯ ; ; ; ; ; ; ; ; ; ,_ ; ‘-,\r\n"
"   .,’ ; ;,-, ; ;, ; ; ;, ; ; ; ; ; ; ; ; ; ; ‘, ; ;’, . . . . .,’ ;,’ ; ; ; ;, ; ; ;,’-, ; ;,’ ‘’~--‘’’\r\n"
"   ,’-~’ ,-‘-~’’ ‘, ,-‘ ‘, ,,- ; ; ; ; ; ; ; ; ‘, ; ; ‘~-,,,-‘’ ; ,’ ; ; ; ; ‘, ;,-‘’ ; ‘, ,-‘,\r\n"
"   .,-‘’ ; ; ; ; ; ‘’ ; ; ;’’ ; ; ; ; ; ; ; ; ; ; ‘’-,,_ ; ; ; _,-‘ ; ; ; ; ; ;’-‘’ ; ; ; ‘’ ; ;’-,\r\n"
"  ..,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;¯¯’’¯ ; ; ; ; ; ; ; ; , ; ; ; ; ; ; ; ; ;’’-,\r\n"
"  ,-‘ ; ; ; ; ; ; ; ,, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; |, ; ; ; ; ; ; ; ; ; ; ‘-,\r\n"
"  .,’ ; ; ; ; ; ; ; ;,’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;|..’-,_ ; ; ; , ; ; ; ; ; ‘,\r\n"
"  ,’ ; ; ; ; ; ; ; ; | ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,’  .’’’,-~’ ; ; ; ; ; ,’\r\n"
"  ’ ; ; ; ; ; ; ; ; ;’~-,,,,,--~~’’’’’’~-,, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,’ ..,-~’’ ; ; ; ; ; ; ,-\r\n"
"   ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ‘, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ’ ,-‘ ; ; ; ; ; ; ; ;,-‘\r\n"
"  , ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ,-‘ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ,’ .’, ; ; ; ; _,,-‘’\r\n"
"  ’, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ,-‘’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,’  .’’~~’’¯\r\n"
"  .’’-, ; ; ; ; ; ; ; ; ; ; ; ; ; ;_,,-‘’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ,-‘\r\n"
"   ’’~-,,_ ; ; ; ; _,,,-~’’ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,-‘\r\n"
"   ..| ; ; ;¯¯’’’’¯ ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,,-‘\r\n"
"   ..’, ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;,-‘\r\n"
"    | ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ; ;|\r\n"
"    ’, ; ; ; ; ; ; ; ; ; ~-,,___ ; ; ; ; ; ; ; ; ; ; ; ; ; ;’,\r\n"
"    .’, ; ; ; ; ; ; ; ; ; ; ;,-‘   ’-, ; ; ; ; ; ; ; ; ; ; ; ; ‘,\r\n"
"   ..,’ ‘- ; ; ; ; ; ; ; ; ;,-‘’   .’-, ; ; ; ; ; ; ; ; ; ; ; ‘,\r\n"
"   .,’ ; ;’ ; ; ; ; ; ; ,,-‘     .’, ; ; ; ; ; ; ; ; ; ; ;’,\r\n"
"   ,’ ; ; ; ; ; ; ; ;,-‘’       ’’-, ; ; ; ; ; ; ; ; ; |\r\n"
"  ..,’ ; ; ; ; ; ; ;,,-‘         ’’, ; ; ; ; ; ; ; ; |\r\n"
"  ..| ; ; ; ; ; ; ;,’          ,’ ; ; ; ; ; ; ; ;,’\r\n"
"  ..| ; ; ; ; ; ; ,’         ..,-‘ ; ; ; ; ; ; ; ,’’\r\n"
"  ..| ; ; ; ; ; ;,’         .,-‘ ; ; ; ; ; ; ; ,-‘\r\n"
"  ..’,_ , ; , ;,’         .,’ ; ; ; ; ; ; ; ,-‘\r\n"
"   ’,,’,¯,’,’’|         .| ; ; ; ; ; ; ; ; ‘--,,\r\n"
"    .¯ ’’         ..’-, ; ; ; ; ; ; ; ; ; ;’’~,,\r\n"
"                 ’’-,, ; ; ; ; ; ; ; ; ; ;’’~-,,\r\n"
"                  ..’’-, ; ; ; ; ; ,,_ ; ;’-,’’-,\r\n"
"                    .’, ; ; ; ; ; ; ‘-,__,\\--\\.\r\n"
"                    ’-, ; ; ;,,-~’’’ \\ , ,|, |\r\n"
"                      ’~-‘’_ , , ,,’,_/--‘\r\n");
}

void silicone()
{
    xyz("                      .¸ - ^^^ ^^^ -^^- -^**^~  ¸\r\n"
"                    ..¸-*´;;;___;;;;;;;;¸  ¸;;;;;;;;;;;;;;¯`^ - \r\n"
"                    .(;¸-*¯¸    ¸.¯¯¯¯ ..¯*^   ¸;;;;;;;;;;;;`^- \r\n"
"                    ¸/´           ¸¸..¯*^ - ;;;;;;;`  \r\n"
"                ..¸’- ^*¯¯*^-     _   _ .`   .`- ;;;;;;;`-¸\r\n"
"                   . *¯¯¯  *^ -`¸  .¸-* -  _..` ¸   ..);;;;;;;;;`\\\r\n"
"                 .¸\\      O¸ . .   |´ . . . . .¯**\\   .¸-´;;;;;;;;;;;)\r\n"
"                   ¸’ *    ¸¸¯-*..¸ ..`¸~~ -O¸ . .  ¸-^´;;;;;;;;;;;;¸-´\r\n"
"                 .¸ -^´    `^.¸/   `     ¸.` -* ..|;;;;;;;;;;;;¸-*\r\n"
"                ¸-*      ¸-*      ¯  ..|;;;;¸-^^¸¸*\r\n"
"               ¸-*      .¸-*  ¸-*¯/      .¯¯ -(\r\n"
"              ¸-*      ¸-*    ¸/         .`\\\r\n"
"             ¸-*     ..¸ -*    ¸-*          ..`\\r\n"
"            ../´     ..¸*     -^´    *-        .\\r\n"
"            ¸/      .`^    ^^*¯    ¸  -¸* `       \\r\n"
"           ..        -*¸   ._¸   - ^*¯¸-*         .’|\r\n"
"           .         .¯`¸   ¯¯ . . .¸  -*           ..|\r\n"
"                   ..  ..`-¸  - ^*¯            ..|\r\n"
"      giggity..giggity..goo       `-¸__¸  -            ¸*\r\n"
"    ¸   ¸      `¸                       ..¸-*\r\n"
"   ..( ..       .`-                      ..¸ *\r\n"
"¸-^****^ -¸* (       ..`       ..^*¯¯¯  *^- ¸         ¸ -*\r\n"
"(¸      ¸ ) ..` ¸       ..`        .. ¸         .¸ -*\r\n"
",´    `¸  ..`¸        ..` -     _  - **^- ¸     .¸ -^*¸\r\n"
">***^^-¸-*~- ¸ .*¸         ..¯  ****  ¯   ¸/;|¯*^~    ^* *;:;¸/^- ¸\r\n"
"(..-¸ .¸)    `-¸             .¸ -^´; ;;’¸   ¸-*;:;:;¸/;:;:;:¯*^-¸\r\n"
"`^- ¸¯¯  ¸ -   `-¸          .¸  -*::`);:;|;:;:;\\ ..¸-*;:;:;:¸/;:;:;¸^*   ¸;:`-¸\r\n"
"  ¯¯¯¯¯..`-    ..`-        .¸ - *::¸::::);:;:;|:;¸   `\\¸/´ ¸;:;:;¸/;:;:(¯:::::::::);:;`¸\r\n"
"      .`-¸   ..`^      ¸  - |;:;:` ´;`  ´;:;¸-:;*:;:;:; ;:;:`  ¸/;:;:;:`\\::::¸ ¸::);:;:;\\r\n"
"       .`      .¯*****¯  .’¸;:;:;:;:;:;:; ;:;:;:;:; ;:;:;:;:;:;:;:;:;¸:`*´;:;` ´;:;:;:’¸\r\n"
"        .`           `-¸;:;:;:;:;¸*;:;:;:;:;:|;:;:;:;:;:;:;:;:; ;:;:;:;:;:;:;:;:;:|\r\n"
"         ..` ¸        ¸ > ¸  -*.|     -;:;:;`¸;:;:;:;:;:;:;:; ;:;:;:;:;:;:;:;:;:;|\r\n"
"           ` -   _     ^* ¯    |;:;:;:;:;:;`¸;:;:;:;:;:;:;:| -  ¸;:;:;:;:;:;:;:|\r\n"
"            .¯¯¯        .`¸;:;::;:;:;:’¸;:;:;:;¸* *-  >* ¯*^- ¸;:;:: \r\n"
"                ..¸*¯¯-¸   ..’¸;:;:;:¸;:;:`¸:;:;:¸*:::::¸/    ¸*>*;`¸\r\n"
"                ..`¸ ..\\    \\  _ *;:;:;:\\;:;:;`^-¸ /    ¸/;:;:;¸  `-¸\r\n"
"              ¸      ` ..`     .\\;:;:_;¸ ¸;:\\¸;:;:¸-*    ¸/;:;:;:¸*:::::`-¸\r\n"
"             ..(      ..`     ___\\¸*_*  -*  *^*    ..¸/;:;:;:;*  ¸::::¸*`-¸\r\n"
"              `¸                  ..¸-*;:;:;:;:;:;:`-¸ *;:;:`-¸\r\n"
"              .’-¸                .._ -*;:;:;¸ ¸;:;:;:;:;:;:;:;:;:;`-¸\r\n"
"               ’¸     .¸-*¯        *¸^^^^^^^^^^^^\\**¯;:;:;:;¸ |::::`**-¸;:;:;¸/´  * - ¸`¸\r\n"
"               .`- ¸  _  -*     |;:;:;:;:;:;:;:;|;`¸;:;:::;(::::::::::*¸;:;¸/;;;;;;;;;;¸*¸\r\n"
"                ..¯¯¯       |;:;:;:¸ ¸;:;:; ;;;;\\;:;:;:;¯-¸:¸ - -*;¸-*;;;;;;;;;;¸* *\r\n"
"                         .|¸-**´:::);:;;|;;;;; \\;:;:;:;:;:;:;:;¸-*;;;;;;;;;;;;¸*\r\n"
"                         . ` - :::*-¸; ;;;; ;;¸;:;:;:;:;:;¸-*;;;;;;;;;;;;¸-*\r\n"
"                          ;;;;;;`- *;:|;;;; ;;;;’¸;:;:;:;¸-*;;;;;;;;;;;;¸-*\r\n"
"                        .. ;;;;;;;;;;`-¸|;;;; ;;;;;;|:;:¸ -*;;;;;;;;;;;;;¸/\r\n"
"                        . ;;;;;;;;;;;;;;;;;;  ;;;;;;;`-*;;;;;;;;;;;;;;;¸/´\r\n"
"                         ;;;;;;;;;;;;;;;;;; ;;;;;;;;;;;;;;;;;;;;;;;;¸-´\r\n"
"                       .. ;;;;;;;;;;;;;;;;;; ;;;;;;;;;;;;;;;;;;;;;;;;¸*\r\n"
"                        ;;;;;;;;;;;;;;;;;;; ;;;;;;;;;;;;;;;;;;;;;;;¸/\r\n"
"                      .. ;;;;;;;;;;;;;;;;;;; ;;;;;;;;;;;;;;;;;;;;;;¸/\r\n"
"                      . ;;;;;;;;;;;;;;;;;;; ;;;;;;;;;;;;;;;;;;;;;;¸*\r\n"
"                     ..¸*;;;;;;;;;;;;;;;;;;;; ;;;;;;;;;;;;;;;;;;;;;; \r\n"
"                     ..|;;;;;;;;;;;;;;;;;;;;¸*;;;;;;;;;;;;;;;;;;;;;;(\r\n"
"                     ..`¸;;;;;;;;;;;;;;;;;;;|;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                      `¸;;;;;;;;;;;;;;;;;;’¸;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                      .`¸;;;;;;;;;;;;;;;;;;`¸;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                       \\;;;;;;;;;;;;;;;;;;`¸;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                       .\\;;;;;;;;;;;;;;;;;;`¸;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                       ..`\\;;;;;;;;;;;;;;;;;;`¸;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                        .\\;;;;;;;;;;;;;;;;;;`¸;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                         ..`¸;;;;;;;;;;;;;;;;;;`¸;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                         .\\;;;;;;;;;;;;;;;;;;`¸;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                         ..`¸;;;;;;;;;;;;;;;;;`\\;;;;;;;;;;;;;;;;;;;;;;;`\\r\n"
"                          `¸;;;;;;;;;;;;;;;;;`\\;;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                          .`¸;;;;;;;;;;;;;;;;;;`¸;;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                           \\;;;;;;;;;;;;;;;;;;`¸;;;;;;;;;;;;;;;;;;;;;;;;`¸\r\n"
"                          .¸ -*~ - ____    -*\\;;;;;;;;;;;;;;;;;;;;;¸  *\r\n"
"                       ._¸  -^*:;:;:;:;:;:;:;:;:;:;:¸ -*;¯*^~    ~^**¯;:’¸\r\n"
"                    .¸-*¯¯¯;:;:;:;:;:;:;:;:;:;:;:;:¸  -*;:;:;:;:;:;:;:;:;:;:;:;:;:;:;:;|\r\n"
"                    .`   _:;:;:;:;:;:___¸   -^*¯;:;:;:;:;:;:;:;:;:;:;:;:¸-¸;:;:;:;:;:|\r\n"
"                      ..¯¯¯¯¯ .(:;:;:;:;:;:;:;:;:;:;:;:;:;:;:;:¸-*..`~~~~^*\r\n"
"                           `*^^~           - *´\r\n");
}

typedef struct {
    int (*callback)(const char *);
    char data[128];
} info_t;

char *wonder_bra;
info_t *info;

void wonder()
{
    xyz("Name of a Company that sells Wonder Bra's?\r\n> ");
    free(wonder_bra);
    wonder_bra = strdup(line());
}

void d_cups()
{
    xyz("Is it a thai girl?\r\n> ");
    if(!strcmp(line(), "yes")) {
        xyz(". . . . . . . . . . . . . . . . _,,, ~~~~~~~~ ,_\r\n"
". . . . . . . . . . . . . . ,-’ : : : :::: :::: :: : : : : :º ‘-, ITS A TRAP!\r\n"
". . . . . . . . . . . . .,-’ :: : : :::: :::: :::: :::: : : :o : ‘-,\r\n"
". . . . . . . . . . . ,-’ :: ::: :: : : :: :::: :::: :: : : : : :O ‘-,\r\n"
". . . . . . . . . .,-’ : :: :: :: :: :: : : : : : , : : :º :::: :::: ::’;\r\n"
". . . . . . . . .,-’ / / : :: :: :: :: : : :::: :::-, ;; ;; ;; ;; ;; ;; ;\\\r\n"
". . . . . . . . /,-’,’ :: : : : : : : : : :: :: :: : ‘-, ;; ;; ;; ;; ;; ;;|\r\n"
". . . . . . . /,’,-’ :: :: :: :: :: :: :: : ::_,-~~,_’-, ;; ;; ;; ;; |\r\n"
". . . . . _/ :,’ :/ :: :: :: : : :: :: _,-’/ : ,-’;'-  ’~-, ;; ;; ;;,’\r\n"
". . . ,-’ / : : : : : : ,- ’ : : :,   :| | /,-’-'  ’__, ’ \\ ;; ;,-’/\r\n"
". . . \\ :/,, : : : _,-’  ,,_ : : \\ :\\ ||/ /,-’-'x### ::\\ \\ ;;/\r\n"
". . . . \\/ /—   : \\ #\\ : :\\ : : \\ :\\ \\| | : (O##º : :/ /- \r\n"
". . . . /,’____ : :\\ ‘-#\\ : \\, : :\\ :\\ \\ \\ : ‘-,___,-’,-`-,,\r\n"
". . . . ‘ ) : : : :   ,, ,,,,,,¯ \\ \\ :: :: ,,_ -,, ’¯ :’- :’-,\r\n"
". . . . .) : : : : : : ,, :   ~~~~’ \\ :: :: :: :  ’¯ :: ,-’ :,/\\\r\n"
". . . . .\\,/ /|\\\\| | :/ / : : : : : : : ,’-, :: :: :: :: ::,   :,-’ \\ \\\r\n"
". . . . .\\\\’|\\\\ \\|/ ‘/ / :: :_ ,, : , | )’; :: :: :: :,-  : ,-’ : : :\\ \\,\r\n"
". . . ./¯ :| \\ |\\ : |/\\ :: ::—-, :\\/ :| / :: :: ,-  : :,-’ : : : : : :  -,,\r\n"
". . ..| : : :/  -(, :: :: ::   ’~,,,,,  :: ,-  : :,-’ : : : : : : : : :,- ’\\\\\\\r\n"
". ,-’ : : : | : :  ) : : :¯  ~-,: : ,  ’ : :,-  : : : : : : : : : ,-’ :¯  ’-,_ .\r\n"
"./ : : : : :’-, :: | :: :: :: _,,-  ¯ : ,   : : : : : : : : : : : / : : : : : : : -,\r\n"
"/ : : : : : -, :¯     ’¯ : : _,,-~  : : : : : : : : : : : : : :| : : : : : : : : :\r\n"
": : : : : : : :¯ ~~~~~~ ’ : : : : : : : : : : : : : : : : : : | : : : : : : : : :\r\n");
    }
}

void android()
{
    xyz("* g o a t s e x * g o a t s e x * g o a t s e x *\r\n"
"g                                               g  \r\n"
"o /     \\             \\            /    \\       o\r\n"
"a|       |             \\          |      |      a\r\n"
"t|       `.             |         |       :     t\r\n"
"s`        |             |        \\|       |     s\r\n"
"e \\       | /       /  \\\\\\   --__ \\\\       :    e\r\n"
"x  \\      \\/   _--~~          ~--__| \\     |    x  \r\n"
"*   \\      \\_-~                    ~-_\\    |    *\r\n"
"g    \\_     \        _.--------.______\\|   |    g\r\n"
"o      \\     \\______// _ ___ _ (_(__>  \\   |    o\r\n"
"a       \\   .  C ___)  ______ (_(____>  |  /    a\r\n"
"t       /\\ |   C ____)/      \\ (_____>  |_/     t\r\n"
"s      / /\\|   C_____)       |  (___>   /  \\    s\r\n"
"e     |   (   _C_____)\\______/  // _/ /     \\   e\r\n"
"x     |    \\  |__   \\_________// (__/       |  x\r\n"
"*    | \\    \\____)   `----   --'             |  *\r\n"
"g    |  \\_          ___\\       /_          _/ | g\r\n"
"o   |              /    |     |  \\            | o\r\n"
"a   |             |    /       \\  \\           | a\r\n"
"t   |          / /    |         |  \\           |t\r\n"
"s   |         / /      \\__/\\___/    |          |s\r\n"
"e  |           /        |    |       |         |e\r\n"
"x  |          |         |    |       |         |x\r\n"
"* g o a t s e x * g o a t s e x * g o a t s e x *\r\n");
}

void cold()
{
    xyz(
"The SCADA Boob Controller does not have available ASCII Art for this\r\n"
"particular type of breasts.\r\n");

    info->callback = (int(*)(const char *)) &cold;
    strcpy(info->data, "Cold Breasts");
}

void pornstar()
{
    info->callback(info->data);
    xyz("Pornstar Breasts vs %s\r\nCalculating", info->data);

    for (int i = 0; i < 5; i++) {
        sleep(1);
        xyz(".");
    }

    xyz("\r\nCalculation failed..\r\n");
}

void perfect()
{
    xyz(
"                      .-''-.                           \r\n"
"                    .`   ::.'.                         \r\n"
"                   /  .:((((\\\\\\                        \r\n"
"                 .' //((`  )))))   \r\n"
"                (  (/)':.__  _/    \r\n"
"               /   /c(   -=\\</^                        \r\n"
"              /   (/j)\\  __.>)                         \r\n"
"             (/  :(r :.'.\\_./                          \r\n"
"             /  .'/    `(`-'                           \r\n"
"            (   '( '``'  '.                            \r\n"
"            /    ))    '   `-.                         \r\n"
"           (  (  ( .    .     `-x                      \r\n"
"           (( ( (: \\    |       )                      \r\n"
"            )|)) )\\Y     \\  `--<                       \r\n"
"             |  `( \\\\    |     |                       \r\n"
"             |    `||    :.    |                       \r\n"
"             `-._  | \\     `-._|                       \r\n"
"                 `-/ :\\_.      ``\\                     \r\n"
"                  /    `'----..../                     \r\n"
"                 /  , .        |/                      \r\n"
"                /               \\                      \r\n"
"               /                |                      \r\n"
"              J    .            |                      \r\n"
"              |    |            |                      \r\n"
"              |  _ _\\__         /                      \r\n"
"              \\      _\\).       |                      \r\n"
"cjr           |       ||        |                      \r\n");
}

void lopsided()
{
    xyz("Nothing to see here.");

    if(!strcmp(info->data, "Cold Breasts")) {
        free(info);
    }
}

void big()
{
    xyz(
"           ,-\\\"    `-,,-\\\"                                        \r\n"
"       _,-'`,        '-,                                        \r\n"
"      '          `-'    `-,_                                    \r\n"
"    ,'                      \\                                   \r\n"
"   /                         \\                                  \r\n"
"  /       v-,       \\     ,   I   \r\n"
" /      ,' ~l       Y     \\   |   \r\n"
"T      /\\   \\  o    I\\     o  |   \r\n"
"|    `/ (_    `-,__,\\\"| `,__,' |                                 \r\n"
"|     \\\" ,( `         f    )   |   \r\n"
"\\     I'\\ `\\,        I    )   \\                                 \r\n"
" \\     L             \\    |    \"                                \r\n"
"  `,   \\    --\\      T   [\\     `                               \r\n"
"   ;    \\             L  ^ \\   |                               \r\n"
"  / I    \\           c-  )  |\\  |                               \r\n"
"  | \\   y I   --.    -   , -|(   \\                              \r\n"
"  |  `\\I/      \\   /  /     \\ (  )                             \r\n"
"  |              I & \\/       |,//                              \r\n"
"  \\              \\//         \\`=                                \r\n"
"   \\              )           \\                                 \r\n"
"    \\             I            |                                \r\n"
"     \\            \"            |                                \r\n"
"      \\           |\\           |                                \r\n"
"       \\          , '_         I                                \r\n"
"        I         I  j      -  L                                \r\n"
"         \\        T  I   ,'  \"                                 \r\n"
"         |        /  |   ,    /                                 \r\n"
"         |       | / `-  `- /                                   \r\n"
"         \\      I /       /\"                                    \r\n"
"          \\      /|     _,\"                                     \r\n"
"           \\    |,\"   ,\"                                        \r\n"
"            (    \\_   \".                                        \r\n"
"    n4bis    \\     \\,   `,                                      \r\n"
"              `'''L-\\_Yl-'                                      \r\n");
}

void high()
{
    system("/bin/ls -al /tmp/boobs | /bin/grep nipple | /bin/grep high");
    strcpy((char *) info, line());
}

struct {
    const char *name;
    const char *cmd;
    void (*func)();
} breasts[] = {
    {"Perfect Breasts", "(o)(o)", &perfect},
    {"Fake Silicone Breasts", "( + )( + )", &silicone},
    {"High Nipple Breasts", "(*)(*)", &high},
    {"Big Nipple Breasts", "(@)(@)", &big},
    {"A Cups", "oo", &a_cups},
    {"D Cups", "{ O }{ O }", &d_cups},
    {"Wonder Bra Breasts", "(oYo)", &wonder},
    {"Cold Breasts", "( ^ )( ^ )", &cold},
    {"Lopsided Breasts", "(o)(O)"},
    {"Pierced Breasts", "(Q)(Q)"},
    {"Hanging Tassels Breasts", "(p)(p)"},
    {"Android Breasts", "|o||o|", &android},
    {"Porn Star Breasts", "($)($)", &pornstar},
};

void boobz0r()
{
    wonder_bra = strdup("SCADA Auxiliary Wonder Bra Company Name");

    info = (info_t *) malloc(sizeof(info_t));
    info->callback = &lopsided;
    strcpy(info->data, "Lopsided Breasts");

    xyz(
"Welcome to the SCADA Boob Controller TM (C) (R)\r\n"
"You are now using the State-of-the-Art Boob Controller Input Validator TM.\r\n"
"Last Login at Boob 'o clock\r\n"
"\r\n");

    while (1) {
        xyz("$ ");
        char *x = line();

        if(!strcmp(x, "help")) {
            xyz(
"The SCADA Boob Controller TM (C) (R) can be handled by using the commands\r\n"
"listed here: http://www.freshsupercool.com/2009/04/04/ascii-boobs/\r\n"
            );
            continue;
        }

        if(!strcmp(x, "info")) {
            xyz(
"SCADA Boob Controller Information Gathering Unit TM.\r\n"
"Wonder Bra Company: %s\r\n", wonder_bra);
        }

        int found = 0;
        for (int i = 0; i < sizeof(breasts) / sizeof(breasts[0]); i++) {
            if(!strcmp(x, breasts[i].cmd)) {
                if(breasts[i].func != NULL) {
                    breasts[i].func();
                }
                found = 1;
                break;
            }
        }

        if(found == 0) {
            xyz("Command not found..\r\n");
        }
    }
}

int main()
{
    WSADATA a;
    WSAStartup(MAKEWORD(2, 2), &a);

    int s = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = 0;
    service.sin_port = htons(0xb00b);

    bind(s, (struct sockaddr *) &service, sizeof(service));

    listen(s, 5);

    while (1) {
        fd = accept(s, NULL, NULL);
        if(fork() == 0) {
            boobz0r();
        }
        close(fd);
    }
}
