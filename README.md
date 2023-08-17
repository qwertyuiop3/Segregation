net_graph 1;cl_updaterate -1;cl_interp_ratio 0;cl_interp 0
```
plans for free time:
https://www.unknowncheats.me/forum/counterstrike-global-offensive/323896-fixing-event-delay-reliable-transmission-fakelagging.html
supposedly will mitigate event delay caused by fakelag yet other causes still remain true
approximate implementation
-
when communication occurs store seqnum at dynamic array
when no communication occurs imitate https://github.com/VSES/SourceEngine2007/blob/master/se2007/engine/cl_main.cpp#L1951
inside packetend check for outack == clc_move::seqnum
	true -> let prediction copy data https://github.com/VSES/SourceEngine2007/blob/master/se2007/engine/servermsghandler.cpp#L176
	false -> abandon call
-
```