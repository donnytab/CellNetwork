package src;

simple PicoSink
{
    parameters:
        @display("i=device/antennatower");
    gates:
//        inout gate[1];
        input in[];
        output out[];
//        output priorityOut[];
//        output priorityOut[];
}

simple MacroCell
{
	parameters:
	    @display("i=device/antennatower;is=l");
	gates:
//	    inout gate[];
        input in[];
//        output out[];
}

simple User
{
	parameters:
	    @display("i=device/cellphone;is=vs");
	gates:
//	    inout gate[1];
//        input in;
        output out;
}

//
// Single-server queue, service rate independent of message length
//
simple Fifo
{
    parameters:
//        volatile double serviceTime @unit(s);
        @display("i=block/queue;q=queue");
        @signal[qlen](type="int");
        @signal[busy](type="bool");
        @signal[queueingTime](type="simtime_t");
        @statistic[qlen](title="queue length";record=vector,timeavg,max;interpolationmode=sample-hold);
        @statistic[busy](title="server busy state";record=vector?,timeavg;interpolationmode=sample-hold);
        @statistic[queueingTime](title="queueing time at dequeue";unit=s;record=vector,mean,max;interpolationmode=none);
    gates:
        input in[];
        output out[];
//        inout fifo;
}

module PicoCell
{
    parameters:
        @display("i=device/antennatower");
    gates:
//        inout gate[1];
        input in[];
        output out[];
    submodules:
        queue: Fifo;
        sink: PicoSink;
    connections:
        for i=0..sizeof(in)-1 {
//        for i=0..2 {
            in[i] --> sink.in++;
            sink.out++ --> queue.in++;
            queue.out++ --> out[i];
        }
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
        user[0].out --> Channel --> pico[0].in++;
        user[1].out --> Channel --> pico[0].in++;
        user[2].out --> Channel --> pico[0].in++;
        user[3].out --> Channel --> pico[1].in++;
        user[4].out --> Channel --> pico[1].in++;
        user[5].out --> Channel --> pico[1].in++;
        user[6].out --> Channel --> pico[2].in++;
        user[7].out --> Channel --> pico[2].in++;
        user[8].out --> Channel --> pico[2].in++;
        user[9].out --> Channel --> pico[3].in++;
        user[10].out --> Channel --> pico[3].in++;
        user[11].out --> Channel --> pico[3].in++;
        
        for k=0..2 {
            macro[0].in++ <-- Channel <-- pico[0].out++;
            macro[0].in++ <-- Channel <-- pico[1].out++;
            macro[0].in++ <-- Channel <-- pico[2].out++;
            macro[0].in++ <-- Channel <-- pico[3].out++;
        }
        
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
