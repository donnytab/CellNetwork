package src;

simple PicoCell
{
    parameters:
        @display("i=device/antennatower");
    gates:
        inout gate[];
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
	    inout gate[];
}

network MicrogridNetwork
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        macro[1]: MacroCell;
        pico[4]: PicoCell;
        user[10]: User;
    connections:
        user[0].gate++ <--> Channel <--> pico[0].gate++;
        user[1].gate++ <--> Channel <--> pico[0].gate++;
        user[2].gate++ <--> Channel <--> pico[0].gate++;
        user[3].gate++ <--> Channel <--> pico[1].gate++;
        user[4].gate++ <--> Channel <--> pico[1].gate++;
        user[5].gate++ <--> Channel <--> pico[1].gate++;
        user[6].gate++ <--> Channel <--> pico[2].gate++;
        user[7].gate++ <--> Channel <--> pico[2].gate++;
        user[8].gate++ <--> Channel <--> pico[3].gate++;
        user[9].gate++ <--> Channel <--> pico[3].gate++;
        macro[0].gate++ <--> Channel <--> pico[0].gate++;
        macro[0].gate++ <--> Channel <--> pico[1].gate++;
        macro[0].gate++ <--> Channel <--> pico[2].gate++;
        macro[0].gate++ <--> Channel <--> pico[3].gate++;
}
