unsigned char x;

enum Keypad_State { SMStart, Wait_One, Read };

int Tick_Fct(int state){
    switch (state){
        case SMStart:
            state = Wait_One;
        break;

        case Wait_One:
            state = Read;
        break;

        case Read:
            state = Read;
        break;
    }

    switch (state){
        case SMStart:
        break;

        case Wait_One:
            x = '\0';
        break;

        case Read:
             x = GetKeypadKey();
        break;
    }

    return state;
}
