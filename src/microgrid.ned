package src;

simple PicoSink
{
    parameters:
        @display("i=device/antennatower");
    gates:
//        inout gate[1];
        input in[];
        output out[];
        output priorityOut[];
}

simple MacroCell
{
	parameters:
	    @display("i=device/antennatower;is=l");
	    @signal[timeSensitiveQueueMsgTime](type="int");
        @signal[timeMediumQueueMsgTime](type="int");
        @signal[timeTolerantQueueMsgTime](type="int");
        @statistic[timeSensitiveQueueMsgTime](title="timeSensitiveQueueMsgTime";record=vector,timeavg,max,min;interpolationmode=sample-hold);
        @statistic[timeMediumQueueMsgTime](title="timeMediumQueueMsgTime";record=vector,timeavg,max,min;interpolationmode=sample-hold);
        @statistic[timeTolerantQueueMsgTime](title="timeTolerantQueueMsgTime";record=vector,timeavg,max,min;interpolationmode=sample-hold);
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
        input in;
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
        @signal[queueLength](type="int");
        @signal[busy](type="bool");
        @signal[queueingTime](type="simtime_t");
        @signal[averageThroughput](type="int");
//        @signal[messageTime](type="simtime_t");

        @statistic[queueLength](title="queue length";record=vector,timeavg,max;interpolationmode=sample-hold);
        @statistic[busy](title="server busy state";record=vector?,timeavg;interpolationmode=sample-hold);
        @statistic[queueingTime](title="queueing time at dequeue";unit=s;record=vector,mean,max;interpolationmode=none);
        @statistic[averageThroughput](title="average throughput";record=vector,timeavg,max;interpolationmode=sample-hold);
//        @statistic[messageTime](title="energy message time";record=vector,mean,max,min;interpolationmode=sample-hold);

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
        output priorityOut[];
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
        
        for j=0..sizeof(priorityOut)-1 {
            sink.priorityOut++ --> priorityOut++;
        }
}

simple NaivePicoCell
{
    parameters:
        @display("i=device/antennatower");
        @signal[averageThroughput](type="int");
//        @signal[messageTime](type="simtime_t");

        @statistic[averageThroughput](title="average throughput";record=vector,timeavg,max;interpolationmode=sample-hold);
//        @statistic[messageTime](title="energy message time";record=vector,mean,max,min;interpolationmode=sample-hold);
    gates:
        input in[];
        output out[];
}

network MicrogridNetwork
{
    types:
        channel Channel extends ned.DatarateChannel {
            delay = 100ms;
        }
    submodules:
//        macro[1]: MacroCell;
//        pico[2]: PicoCell;
//        user[50]: User;
        macro[1]: MacroCell;
        pico[4]: PicoCell;
        user[48]: User;
    connections:
        user[0].out --> Channel --> pico[0].in++;
        user[1].out --> Channel --> pico[0].in++;
        user[2].out --> Channel --> pico[0].in++;
        user[3].out --> Channel --> pico[0].in++;
        user[4].out --> Channel --> pico[0].in++;
        user[5].out --> Channel --> pico[0].in++;
        user[6].out --> Channel --> pico[0].in++;
        user[7].out --> Channel --> pico[0].in++;
        user[8].out --> Channel --> pico[0].in++;
        user[9].out --> Channel --> pico[0].in++;
        user[10].out --> Channel --> pico[0].in++;
        user[11].out --> Channel --> pico[0].in++;
        user[12].out --> Channel --> pico[1].in++;
        user[13].out --> Channel --> pico[1].in++;
        user[14].out --> Channel --> pico[1].in++;
        user[15].out --> Channel --> pico[1].in++;
        user[16].out --> Channel --> pico[1].in++;
        user[17].out --> Channel --> pico[1].in++;
        user[18].out --> Channel --> pico[1].in++;
        user[19].out --> Channel --> pico[1].in++;
        user[20].out --> Channel --> pico[1].in++;
        user[21].out --> Channel --> pico[1].in++;
        user[22].out --> Channel --> pico[1].in++;
        user[23].out --> Channel --> pico[1].in++;
        user[24].out --> Channel --> pico[2].in++;
        user[25].out --> Channel --> pico[2].in++;
        user[26].out --> Channel --> pico[2].in++;
        user[27].out --> Channel --> pico[2].in++;
        user[28].out --> Channel --> pico[2].in++;
        user[29].out --> Channel --> pico[2].in++;
        user[30].out --> Channel --> pico[2].in++;
        user[31].out --> Channel --> pico[2].in++;
        user[32].out --> Channel --> pico[2].in++;
        user[33].out --> Channel --> pico[2].in++;
        user[34].out --> Channel --> pico[2].in++;
        user[35].out --> Channel --> pico[2].in++;
        user[36].out --> Channel --> pico[3].in++;
        user[37].out --> Channel --> pico[3].in++;
        user[38].out --> Channel --> pico[3].in++;
        user[39].out --> Channel --> pico[3].in++;
        user[40].out --> Channel --> pico[3].in++;
        user[41].out --> Channel --> pico[3].in++;
        user[42].out --> Channel --> pico[3].in++;
        user[43].out --> Channel --> pico[3].in++;
        user[44].out --> Channel --> pico[3].in++;
        user[45].out --> Channel --> pico[3].in++;
        user[46].out --> Channel --> pico[3].in++;
        user[47].out --> Channel --> pico[3].in++;
//        user[48].out --> Channel --> pico[3].in++;
//        user[49].out --> Channel --> pico[3].in++;
//        user[50].out --> Channel --> pico[3].in++;
//        user[51].out --> Channel --> pico[3].in++;
//        user[52].out --> Channel --> pico[3].in++;
//        user[53].out --> Channel --> pico[3].in++;
//        user[54].out --> Channel --> pico[3].in++;
//        user[55].out --> Channel --> pico[3].in++;
//        user[56].out --> Channel --> pico[3].in++;
//        user[57].out --> Channel --> pico[3].in++;
//        user[58].out --> Channel --> pico[3].in++;
//        user[59].out --> Channel --> pico[3].in++;
//        user[60].out --> Channel --> pico[3].in++;
//        user[61].out --> Channel --> pico[3].in++;
//        user[62].out --> Channel --> pico[3].in++;
//        user[63].out --> Channel --> pico[3].in++;
//        user[64].out --> Channel --> pico[3].in++;
//        user[65].out --> Channel --> pico[3].in++;
//        user[66].out --> Channel --> pico[3].in++;
//        user[67].out --> Channel --> pico[3].in++;
//        user[68].out --> Channel --> pico[3].in++;
//        user[69].out --> Channel --> pico[3].in++;
//        user[70].out --> Channel --> pico[3].in++;
//        user[71].out --> Channel --> pico[3].in++;
//        user[72].out --> Channel --> pico[3].in++;
//        user[73].out --> Channel --> pico[3].in++;
//        user[74].out --> Channel --> pico[3].in++;
//        user[75].out --> Channel --> pico[3].in++;
//        user[76].out --> Channel --> pico[3].in++;
//        user[77].out --> Channel --> pico[3].in++;
//        user[78].out --> Channel --> pico[3].in++;
//        user[79].out --> Channel --> pico[3].in++;
//        user[80].out --> Channel --> pico[3].in++;
//        user[81].out --> Channel --> pico[3].in++;
//        user[82].out --> Channel --> pico[3].in++;
//        user[83].out --> Channel --> pico[3].in++;
//        user[84].out --> Channel --> pico[3].in++;
//        user[85].out --> Channel --> pico[3].in++;
//        user[86].out --> Channel --> pico[3].in++;
//        user[87].out --> Channel --> pico[3].in++;
//        user[88].out --> Channel --> pico[3].in++;
//        user[89].out --> Channel --> pico[3].in++;
//        user[90].out --> Channel --> pico[3].in++;
//        user[91].out --> Channel --> pico[3].in++;
//        user[92].out --> Channel --> pico[3].in++;
//        user[93].out --> Channel --> pico[3].in++;
//        user[94].out --> Channel --> pico[3].in++;
//        user[95].out --> Channel --> pico[3].in++;
//        user[96].out --> Channel --> pico[3].in++;
//        user[97].out --> Channel --> pico[3].in++;
//        user[98].out --> Channel --> pico[3].in++;
//        user[99].out --> Channel --> pico[3].in++;
        
        user[0].in <-- Channel <-- pico[0].priorityOut++;
        user[1].in <-- Channel <-- pico[0].priorityOut++;
        user[2].in <-- Channel <-- pico[0].priorityOut++;
        user[3].in <-- Channel <-- pico[0].priorityOut++;
        user[4].in <-- Channel <-- pico[0].priorityOut++;
        user[5].in <-- Channel <-- pico[0].priorityOut++;
        user[6].in <-- Channel <-- pico[0].priorityOut++;
        user[7].in <-- Channel <-- pico[0].priorityOut++;
        user[8].in <-- Channel <-- pico[0].priorityOut++;
        user[9].in <-- Channel <-- pico[0].priorityOut++;
        user[10].in <-- Channel <-- pico[0].priorityOut++;
        user[11].in <-- Channel <-- pico[0].priorityOut++;
        user[12].in <-- Channel <-- pico[1].priorityOut++;
        user[13].in <-- Channel <-- pico[1].priorityOut++;
        user[14].in <-- Channel <-- pico[1].priorityOut++;
        user[15].in <-- Channel <-- pico[1].priorityOut++;
        user[16].in <-- Channel <-- pico[1].priorityOut++;
        user[17].in <-- Channel <-- pico[1].priorityOut++;
        user[18].in <-- Channel <-- pico[1].priorityOut++;
        user[19].in <-- Channel <-- pico[1].priorityOut++;
        user[20].in <-- Channel <-- pico[1].priorityOut++;
        user[21].in <-- Channel <-- pico[1].priorityOut++;
        user[22].in <-- Channel <-- pico[1].priorityOut++;
        user[23].in <-- Channel <-- pico[1].priorityOut++;
        user[24].in <-- Channel <-- pico[2].priorityOut++;
        user[25].in <-- Channel <-- pico[2].priorityOut++;
        user[26].in <-- Channel <-- pico[2].priorityOut++;
        user[27].in <-- Channel <-- pico[2].priorityOut++;
        user[28].in <-- Channel <-- pico[2].priorityOut++;
        user[29].in <-- Channel <-- pico[2].priorityOut++;
        user[30].in <-- Channel <-- pico[2].priorityOut++;
        user[31].in <-- Channel <-- pico[2].priorityOut++;
        user[32].in <-- Channel <-- pico[2].priorityOut++;
        user[33].in <-- Channel <-- pico[2].priorityOut++;
        user[34].in <-- Channel <-- pico[2].priorityOut++;
        user[35].in <-- Channel <-- pico[2].priorityOut++;
        user[36].in <-- Channel <-- pico[3].priorityOut++;
        user[37].in <-- Channel <-- pico[3].priorityOut++;
        user[38].in <-- Channel <-- pico[3].priorityOut++;
        user[39].in <-- Channel <-- pico[3].priorityOut++;
        user[40].in <-- Channel <-- pico[3].priorityOut++;
        user[41].in <-- Channel <-- pico[3].priorityOut++;
        user[42].in <-- Channel <-- pico[3].priorityOut++;
        user[43].in <-- Channel <-- pico[3].priorityOut++;
        user[44].in <-- Channel <-- pico[3].priorityOut++;
        user[45].in <-- Channel <-- pico[3].priorityOut++;
        user[46].in <-- Channel <-- pico[3].priorityOut++;
        user[47].in <-- Channel <-- pico[3].priorityOut++;
//        user[48].in <-- Channel <-- pico[3].priorityOut++;
//        user[49].in <-- Channel <-- pico[3].priorityOut++;
//        user[50].in <-- Channel <-- pico[3].priorityOut++;
//        user[51].in <-- Channel <-- pico[3].priorityOut++;
//        user[52].in <-- Channel <-- pico[3].priorityOut++;
//        user[53].in <-- Channel <-- pico[3].priorityOut++;
//        user[54].in <-- Channel <-- pico[3].priorityOut++;
//        user[55].in <-- Channel <-- pico[3].priorityOut++;
//        user[56].in <-- Channel <-- pico[3].priorityOut++;
//        user[57].in <-- Channel <-- pico[3].priorityOut++;
//        user[58].in <-- Channel <-- pico[3].priorityOut++;
//        user[59].in <-- Channel <-- pico[3].priorityOut++;
//        user[60].in <-- Channel <-- pico[3].priorityOut++;
//        user[61].in <-- Channel <-- pico[3].priorityOut++;
//        user[62].in <-- Channel <-- pico[3].priorityOut++;
//        user[63].in <-- Channel <-- pico[3].priorityOut++;
//        user[64].in <-- Channel <-- pico[3].priorityOut++;
//        user[65].in <-- Channel <-- pico[3].priorityOut++;
//        user[66].in <-- Channel <-- pico[3].priorityOut++;
//        user[67].in <-- Channel <-- pico[3].priorityOut++;
//        user[68].in <-- Channel <-- pico[3].priorityOut++;
//        user[69].in <-- Channel <-- pico[3].priorityOut++;
//        user[70].in <-- Channel <-- pico[3].priorityOut++;
//        user[71].in <-- Channel <-- pico[3].priorityOut++;
//        user[72].in <-- Channel <-- pico[3].priorityOut++;
//        user[73].in <-- Channel <-- pico[3].priorityOut++;
//        user[74].in <-- Channel <-- pico[3].priorityOut++;
//        user[75].in <-- Channel <-- pico[3].priorityOut++;
//        user[76].in <-- Channel <-- pico[3].priorityOut++;
//        user[77].in <-- Channel <-- pico[3].priorityOut++;
//        user[78].in <-- Channel <-- pico[3].priorityOut++;
//        user[79].in <-- Channel <-- pico[3].priorityOut++;
//        user[80].in <-- Channel <-- pico[3].priorityOut++;
//        user[81].in <-- Channel <-- pico[3].priorityOut++;
//        user[82].in <-- Channel <-- pico[3].priorityOut++;
//        user[83].in <-- Channel <-- pico[3].priorityOut++;
//        user[84].in <-- Channel <-- pico[3].priorityOut++;
//        user[85].in <-- Channel <-- pico[3].priorityOut++;
//        user[86].in <-- Channel <-- pico[3].priorityOut++;
//        user[87].in <-- Channel <-- pico[3].priorityOut++;
//        user[88].in <-- Channel <-- pico[3].priorityOut++;
//        user[89].in <-- Channel <-- pico[3].priorityOut++;
//        user[90].in <-- Channel <-- pico[3].priorityOut++;
//        user[91].in <-- Channel <-- pico[3].priorityOut++;
//        user[92].in <-- Channel <-- pico[3].priorityOut++;
//        user[93].in <-- Channel <-- pico[3].priorityOut++;
//        user[94].in <-- Channel <-- pico[3].priorityOut++;
//        user[95].in <-- Channel <-- pico[3].priorityOut++;
//        user[96].in <-- Channel <-- pico[3].priorityOut++;
//        user[97].in <-- Channel <-- pico[3].priorityOut++;
//        user[98].in <-- Channel <-- pico[3].priorityOut++;
//        user[99].in <-- Channel <-- pico[3].priorityOut++;
        
        for k=0..11 {
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


network HeterogeneousMicrogridNetwork
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        macro[1]: MacroCell;
        pico[4]: PicoCell;
        user[50]: User;
    connections:
        user[0].out --> Channel --> pico[0].in++;
        user[1].out --> Channel --> pico[0].in++;
        user[2].out --> Channel --> pico[0].in++;
        user[3].out --> Channel --> pico[0].in++;
        user[4].out --> Channel --> pico[0].in++;
        user[5].out --> Channel --> pico[1].in++;
        user[6].out --> Channel --> pico[1].in++;
        user[7].out --> Channel --> pico[1].in++;
        user[8].out --> Channel --> pico[1].in++;
        user[9].out --> Channel --> pico[1].in++;
        user[10].out --> Channel --> pico[1].in++;
        user[11].out --> Channel --> pico[1].in++;
        user[12].out --> Channel --> pico[1].in++;
        user[13].out --> Channel --> pico[1].in++;
        user[14].out --> Channel --> pico[1].in++;
        user[15].out --> Channel --> pico[2].in++;
        user[16].out --> Channel --> pico[2].in++;
        user[17].out --> Channel --> pico[2].in++;
        user[18].out --> Channel --> pico[2].in++;
        user[19].out --> Channel --> pico[2].in++;
        user[20].out --> Channel --> pico[2].in++;
        user[21].out --> Channel --> pico[2].in++;
        user[22].out --> Channel --> pico[2].in++;
        user[23].out --> Channel --> pico[2].in++;
        user[24].out --> Channel --> pico[2].in++;
        user[25].out --> Channel --> pico[2].in++;
        user[26].out --> Channel --> pico[2].in++;
        user[27].out --> Channel --> pico[2].in++;
        user[28].out --> Channel --> pico[2].in++;
        user[29].out --> Channel --> pico[2].in++;
        user[30].out --> Channel --> pico[3].in++;
        user[31].out --> Channel --> pico[3].in++;
        user[32].out --> Channel --> pico[3].in++;
        user[33].out --> Channel --> pico[3].in++;
        user[34].out --> Channel --> pico[3].in++;
        user[35].out --> Channel --> pico[3].in++;
        user[36].out --> Channel --> pico[3].in++;
        user[37].out --> Channel --> pico[3].in++;
        user[38].out --> Channel --> pico[3].in++;
        user[39].out --> Channel --> pico[3].in++;
        user[40].out --> Channel --> pico[3].in++;
        user[41].out --> Channel --> pico[3].in++;
        user[42].out --> Channel --> pico[3].in++;
        user[43].out --> Channel --> pico[3].in++;
        user[44].out --> Channel --> pico[3].in++;
        user[45].out --> Channel --> pico[3].in++;
        user[46].out --> Channel --> pico[3].in++;
        user[47].out --> Channel --> pico[3].in++;
        user[48].out --> Channel --> pico[3].in++;
        user[49].out --> Channel --> pico[3].in++;
        
        user[0].in <-- Channel <-- pico[0].priorityOut++;
        user[1].in <-- Channel <-- pico[0].priorityOut++;
        user[2].in <-- Channel <-- pico[0].priorityOut++;
        user[3].in <-- Channel <-- pico[0].priorityOut++;
        user[4].in <-- Channel <-- pico[0].priorityOut++;
        user[5].in <-- Channel <-- pico[1].priorityOut++;
        user[6].in <-- Channel <-- pico[1].priorityOut++;
        user[7].in <-- Channel <-- pico[1].priorityOut++;
        user[8].in <-- Channel <-- pico[1].priorityOut++;
        user[9].in <-- Channel <-- pico[1].priorityOut++;
        user[10].in <-- Channel <-- pico[1].priorityOut++;
        user[11].in <-- Channel <-- pico[1].priorityOut++;
        user[12].in <-- Channel <-- pico[1].priorityOut++;
        user[13].in <-- Channel <-- pico[1].priorityOut++;
        user[14].in <-- Channel <-- pico[1].priorityOut++;
        user[15].in <-- Channel <-- pico[2].priorityOut++;
        user[16].in <-- Channel <-- pico[2].priorityOut++;
        user[17].in <-- Channel <-- pico[2].priorityOut++;
        user[18].in <-- Channel <-- pico[2].priorityOut++;
        user[19].in <-- Channel <-- pico[2].priorityOut++;
        user[20].in <-- Channel <-- pico[2].priorityOut++;
        user[21].in <-- Channel <-- pico[2].priorityOut++;
        user[22].in <-- Channel <-- pico[2].priorityOut++;
        user[23].in <-- Channel <-- pico[2].priorityOut++;
        user[24].in <-- Channel <-- pico[2].priorityOut++;
        user[25].in <-- Channel <-- pico[2].priorityOut++;
        user[26].in <-- Channel <-- pico[2].priorityOut++;
        user[27].in <-- Channel <-- pico[2].priorityOut++;
        user[28].in <-- Channel <-- pico[2].priorityOut++;
        user[29].in <-- Channel <-- pico[2].priorityOut++;
        user[30].in <-- Channel <-- pico[3].priorityOut++;
        user[31].in <-- Channel <-- pico[3].priorityOut++;
        user[32].in <-- Channel <-- pico[3].priorityOut++;
        user[33].in <-- Channel <-- pico[3].priorityOut++;
        user[34].in <-- Channel <-- pico[3].priorityOut++;
        user[35].in <-- Channel <-- pico[3].priorityOut++;
        user[36].in <-- Channel <-- pico[3].priorityOut++;
        user[37].in <-- Channel <-- pico[3].priorityOut++;
        user[38].in <-- Channel <-- pico[3].priorityOut++;
        user[39].in <-- Channel <-- pico[3].priorityOut++;
        user[40].in <-- Channel <-- pico[3].priorityOut++;
        user[41].in <-- Channel <-- pico[3].priorityOut++;
        user[42].in <-- Channel <-- pico[3].priorityOut++;
        user[43].in <-- Channel <-- pico[3].priorityOut++;
        user[44].in <-- Channel <-- pico[3].priorityOut++;
        user[45].in <-- Channel <-- pico[3].priorityOut++;
        user[46].in <-- Channel <-- pico[3].priorityOut++;
        user[47].in <-- Channel <-- pico[3].priorityOut++;
        user[48].in <-- Channel <-- pico[3].priorityOut++;
        user[49].in <-- Channel <-- pico[3].priorityOut++;
        
        for k=0..4 {
            macro[0].in++ <-- Channel <-- pico[0].out++;
        }
        
        for k=0..9 {
            macro[0].in++ <-- Channel <-- pico[1].out++;
        }
        
        for k=0..14 {
            macro[0].in++ <-- Channel <-- pico[2].out++;
        }
        
        for k=0..19 {
            macro[0].in++ <-- Channel <-- pico[3].out++;
        }
}

network NaiveUniformMicrogridNetwork
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 500ms;
        }
    submodules:
        macro[1]: MacroCell;
        pico[4]: NaivePicoCell;
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

        macro[0].in++ <-- Channel <-- pico[0].out++;
        macro[0].in++ <-- Channel <-- pico[1].out++;
        macro[0].in++ <-- Channel <-- pico[2].out++;
        macro[0].in++ <-- Channel <-- pico[3].out++;

        user[0].in <-- Channel <-- pico[0].out++;
        user[1].in <-- Channel <-- pico[0].out++;
        user[2].in <-- Channel <-- pico[0].out++;
        user[3].in <-- Channel <-- pico[1].out++;
        user[4].in <-- Channel <-- pico[1].out++;
        user[5].in <-- Channel <-- pico[1].out++;
        user[6].in <-- Channel <-- pico[2].out++;
        user[7].in <-- Channel <-- pico[2].out++;
        user[8].in <-- Channel <-- pico[2].out++;
        user[9].in <-- Channel <-- pico[3].out++;
        user[10].in <-- Channel <-- pico[3].out++;
        user[11].in <-- Channel <-- pico[3].out++;
}
