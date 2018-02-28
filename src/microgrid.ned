package src;

simple PicoCell
{
    parameters:
        @display("i=device/antennatower");
    gates:
        inout gate[1];
}

simple MacroCell
{
	parameters:
	    @display("i=device/antennatower;is=l");
	gates:
	    inout gate[];
}

simple User
{
	parameters:
	    @display("i=device/cellphone;is=vs");
	gates:
	    inout gate[1];
}

network MicrogridNetwork
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
//        macro[1]: MacroCell;
//        pico[2]: PicoCell;
//        user[50]: User;
        macro[1]: MacroCell;
        pico[4]: PicoCell;
        user[12]: User;
    connections:
        macro[0].gate++ <--> Channel <--> pico[0].gate[0];
        macro[0].gate++ <--> Channel <--> pico[1].gate[0];
        macro[0].gate++ <--> Channel <--> pico[2].gate[0];
        macro[0].gate++ <--> Channel <--> pico[3].gate[0];
        user[0].gate++ <--> Channel <--> pico[0].gate++;
        user[1].gate++ <--> Channel <--> pico[0].gate++;
        user[2].gate++ <--> Channel <--> pico[0].gate++;
        user[3].gate++ <--> Channel <--> pico[1].gate++;
        user[4].gate++ <--> Channel <--> pico[1].gate++;
        user[5].gate++ <--> Channel <--> pico[1].gate++;
        user[6].gate++ <--> Channel <--> pico[2].gate++;
        user[7].gate++ <--> Channel <--> pico[2].gate++;
        user[8].gate++ <--> Channel <--> pico[2].gate++;
        user[9].gate++ <--> Channel <--> pico[3].gate++;
        user[10].gate++ <--> Channel <--> pico[3].gate++;
        user[11].gate++ <--> Channel <--> pico[3].gate++;
        
//        user[0].gate++ <--> Channel <--> pico[0].gate++;
//        user[1].gate++ <--> Channel <--> pico[0].gate++;
//        user[2].gate++ <--> Channel <--> pico[0].gate++;
//        user[3].gate++ <--> Channel <--> pico[0].gate++;
//        user[4].gate++ <--> Channel <--> pico[0].gate++;
//        user[5].gate++ <--> Channel <--> pico[0].gate++;
//        user[6].gate++ <--> Channel <--> pico[0].gate++;
//        user[7].gate++ <--> Channel <--> pico[0].gate++;
//        user[8].gate++ <--> Channel <--> pico[0].gate++;
//        user[9].gate++ <--> Channel <--> pico[0].gate++;
//        user[10].gate++ <--> Channel <--> pico[0].gate++;
//        user[11].gate++ <--> Channel <--> pico[0].gate++;
//        user[12].gate++ <--> Channel <--> pico[0].gate++;
//        user[13].gate++ <--> Channel <--> pico[0].gate++;
//        user[14].gate++ <--> Channel <--> pico[0].gate++;
//        user[15].gate++ <--> Channel <--> pico[0].gate++;
//        user[16].gate++ <--> Channel <--> pico[0].gate++;
//        user[17].gate++ <--> Channel <--> pico[0].gate++;
//        user[18].gate++ <--> Channel <--> pico[0].gate++;
//        user[19].gate++ <--> Channel <--> pico[0].gate++;
//        user[20].gate++ <--> Channel <--> pico[0].gate++;
//        user[21].gate++ <--> Channel <--> pico[0].gate++;
//        user[22].gate++ <--> Channel <--> pico[0].gate++;
//        user[23].gate++ <--> Channel <--> pico[0].gate++;
//        user[24].gate++ <--> Channel <--> pico[0].gate++;
//        
//        user[25].gate++ <--> Channel <--> pico[1].gate++;
//        user[26].gate++ <--> Channel <--> pico[1].gate++;
//        user[27].gate++ <--> Channel <--> pico[1].gate++;
//        user[28].gate++ <--> Channel <--> pico[1].gate++;
//        user[29].gate++ <--> Channel <--> pico[1].gate++;
//        user[30].gate++ <--> Channel <--> pico[1].gate++;
//        user[31].gate++ <--> Channel <--> pico[1].gate++;
//        user[32].gate++ <--> Channel <--> pico[1].gate++;
//        user[33].gate++ <--> Channel <--> pico[1].gate++;
//        user[34].gate++ <--> Channel <--> pico[1].gate++;
//        user[35].gate++ <--> Channel <--> pico[1].gate++;
//        user[36].gate++ <--> Channel <--> pico[1].gate++;
//        user[37].gate++ <--> Channel <--> pico[1].gate++;
//        user[38].gate++ <--> Channel <--> pico[1].gate++;
//        user[39].gate++ <--> Channel <--> pico[1].gate++;
//        user[40].gate++ <--> Channel <--> pico[1].gate++;
//        user[41].gate++ <--> Channel <--> pico[1].gate++;
//        user[42].gate++ <--> Channel <--> pico[1].gate++;
//        user[43].gate++ <--> Channel <--> pico[1].gate++;
//        user[44].gate++ <--> Channel <--> pico[1].gate++;
//        user[45].gate++ <--> Channel <--> pico[1].gate++;
//        user[46].gate++ <--> Channel <--> pico[1].gate++;
//        user[47].gate++ <--> Channel <--> pico[1].gate++;
//        user[48].gate++ <--> Channel <--> pico[1].gate++;
//        user[49].gate++ <--> Channel <--> pico[1].gate++;
}
