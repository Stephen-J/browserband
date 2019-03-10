#include <emscripten/emscripten.h>
#include <stdlib.h>
#include <string.h>

//defines copied from ui-event.h
#define ARROW_DOWN    0x80
#define ARROW_LEFT    0x81
#define ARROW_RIGHT   0x82
#define ARROW_UP      0x83

#define KC_F1         0x84
#define KC_F2         0x85
#define KC_F3         0x86
#define KC_F4         0x87
#define KC_F5         0x88
#define KC_F6         0x89
#define KC_F7         0x8A
#define KC_F8         0x8B
#define KC_F9         0x8C
#define KC_F10        0x8D
#define KC_F11        0x8E
#define KC_F12        0x8F
#define KC_F13        0x90
#define KC_F14        0x91
#define KC_F15        0x92

#define KC_HELP       0x93
#define KC_HOME       0x94
#define KC_PGUP       0x95
#define KC_END        0x96
#define KC_PGDOWN     0x97
#define KC_INSERT     0x98
#define KC_PAUSE      0x99
#define KC_BREAK      0x9a
#define KC_BEGIN      0x9b
#define KC_ENTER      0x9c /* ASCII \r */
#define KC_TAB        0x9d /* ASCII \t */
#define KC_DELETE     0x9e
#define KC_BACKSPACE  0x9f /* ASCII \h */
#define ESCAPE        0xE000

worker_handle worker;

void cback(char* data, int size, void* arg) {
    int keyCode;
    char k;
    switch(data[0]){
        case 1 : 
            EM_ASM(
                AngbandModule.TermInitJsm();
                );
            break;
        case 2 :
            //EM_ASM(console.log("TermNukeJsm"));
            break;
        case 3 :
            // this does nothing right now, 
            keyCode = 0;
            keyCode = EM_ASM_INT({
                //console.log("TermExtraEvent -> " + AngbandModule.keyPress);
                var k = AngbandModule.keyPress;
                AngbandModule.keyPress = 0;
                return k
            });
            k = keyCode;
            break;
        case 4 :
            //EM_ASM(console.log("TermExtraFlush"));
            break;
        case 5 :
            EM_ASM(
                //console.log("TermExtraClear");
                AngbandModule.TermExtraClear();
                );
            break;
        case 6 :
            //EM_ASM(console.log("TermExtraShape"));
            break;
        case 7 :
            //EM_ASM(console.log("TermExtraFrosh"));
            break;
        case 8 :
            //EM_ASM(console.log("TermExtraFresh"));
            break;
        case 9 :
            //EM_ASM(console.log("TermExtraNoise"));
            break;
        case 10 :
            //EM_ASM(console.log("TermExtraBored"));
            break;
        case 11 :
            //EM_ASM(console.log("TermExtraReact"));
            break;
        case 12 :
            //EM_ASM(console.log("TermExtraAlive"));
            break;
        case 13 :
            //EM_ASM(console.log("TermExtraLevel"));
            break;
        case 14 :
            //EM_ASM(console.log("TermExtraDelay"));
            break;
        case 15 :
            //EM_ASM(console.log("TermWipeJsm"));
            break;
        case 16 :
            EM_ASM_({
                var c = [];
                for(i = 0 ; i < $2 ; i++){
                    c.push(getValue($3 + i,"i8"));
                }
                var a = [];
                for(i = 0 ; i < $2 ; i++){
                    a.push(getValue($4 + i,"i8"));
                }
                var tc = [];
                for(i = 0 ; i < $2 ; i++){
                    tc.push(getValue($5 + i,"i8"));
                }
                AngbandModule.TermPictJsm($0,$1,$2,c,a,tc);
                },data[1] /*x*/,data[2]/*y*/,data[3]/*n*/,&data[4]/*cp*/,&data[4 + data[3]]/*ap*/,&data[4 + 2 * data[3]]/*tc*/);
                break;
            case 17 :
                EM_ASM_({
                    AngbandModule.TermCursJsm($0,$1);
                },data[1],data[2]);
                break;
    }
}

EMSCRIPTEN_KEEPALIVE void start_band_worker(char *angbandModule {
    EM_ASM_({
        console.log(Pointer_stringify($0));
    },data);
    int hasAngband = EM_ASM_INT({
        var hasAngband = 1;
        try{
            AngbandModule;
        }catch(error){
            console.error("angband object required");
            hasAngband = 0;
        }
        return hasAngband;
    });

    if(hasAngband){
        worker = emscripten_create_worker(angbandModule);
        emscripten_call_worker(worker, "start", 0, 0, cback, (void*)42);
    }
    //return 0;
}

/*
convert javascript keycodes to angband codes (ui-event.h) and pass
on to the angband worker
*/
EMSCRIPTEN_KEEPALIVE void keypress(int keyCode){
    int k = keyCode;
    switch(keyCode){
        case 8 :
            k = KC_BACKSPACE;
            break;
        case  9 :
            k = KC_TAB;
            break;
        case 13 :
            k = KC_ENTER;
            break;
        case 27 :
            k = ESCAPE;
            break;
        case 37 :
            k = ARROW_LEFT;
            break;
        case 38 :
            k = ARROW_UP;
            break;
        case 39 :
            k = ARROW_RIGHT;
            break;
        case 40 :
            k = ARROW_DOWN;
            break;
        case 46 :
            k = KC_DELETE;
            break;
        case 190 : // period
            k = 46;
            break;
    }
    //EM_ASM_({
     //   console.log("MAIN keypress -> " + $0);
    //},k);
    emscripten_call_worker(worker,"keypress",(char*)&k,4,cback,(void*)42);
}

EMSCRIPTEN_KEEPALIVE void testPrint(){
    EM_ASM(console.log("Testprint"));
    //emscripten_call_worker(worker, "testPrint", 0, 0, cback, (void*)42);
}

EMSCRIPTEN_KEEPALIVE void kill(){
    emscripten_destroy_worker(worker);
}
