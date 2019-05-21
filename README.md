# iosbitmapdecoding
Experimenting with bitmap decoding on ios 

Inspired by this blog post...

 - Really fast bitset decoding for “average” densities https://lemire.me/blog/2019/05/03/really-fast-bitset-decoding-for-average-densities/


## Requirements

- A recent mac with Xcode installed
- A recent iOS device


## Usage

- Open BitmapDecoding.xcodeproj in Xcode (macOS) 
- Click on the "BitmapDecoding" project within Xcode, go to "Identity" and select a valid account under "Team".
- Plug your device (e.g., iPhone) in your mac.
- In Xcode, go to Window > Devices. This will open a new window. You should see your device in this new window. Don't lose this new window.
- In Xcode, go to Product > Build For > Running
- You should see in Xcode under Products "BitmapDecoding.app", drag and drop it into the "Devices" window we opened previously.
- You should now see the app on your device. By default, iOS won't let you run it, so go under Settings > General. You will find a setting there to allow you to run the app.
- Run the app.

## Using Instruments

Apple has a tool called Instruments as part of Xcode that can be used to record the number of instructions (FIXED_INSTRUCTIONS) and the number of cycles (FIXED_CYCLES). First build and upload your app. Connect your device to your mac and launch Instruments, select the "Counters" template and your device and app. Then go to File > Recording Options and click the + in the “Events and Formulas” section, and pick the events FIXED_INSTRUCTIONS and FIXED_CYCLES and sample by time. 

For this app, I found that FIXED_INSTRUCTIONS goes up to 29346274130 whereas FIXED_CYCLES goes up to 9408002514 for an average of 3.12 instructions per cycle. TIt is much higher than on x64 where the highest I reach for part of the benchmark is 2.6 instructions per cycle.

## Sample result

iPhone XR, Xcode 10.1
```
Measuring frequency
Median frequency detected: 2.131252 GHz (939 samples out of 1000). 
129996 129996 
basic_decoder timing: 47.445 nanoseconds per set bit 
simdjson_decoder timing: 11.264  nanoseconds per set bit  
basic_decoder: 101.117 cycles per set bit 
simdjson_decoder: 24.007 cycles per set bit  
Measuring frequency
Median frequency detected: 2.496610 GHz (964 samples out of 1000). 
129996 129996 
basic_decoder timing: 1.652 nanoseconds per set bit 
simdjson_decoder timing: 1.200  nanoseconds per set bit  
basic_decoder: 4.125 cycles per set bit 
simdjson_decoder: 2.997 cycles per set bit  
Measuring frequency
Median frequency detected: 2.496610 GHz (970 samples out of 1000). 
129996 129996 
basic_decoder timing: 1.652 nanoseconds per set bit 
simdjson_decoder timing: 1.197  nanoseconds per set bit  
basic_decoder: 4.125 cycles per set bit 
simdjson_decoder: 2.989 cycles per set bit  
Measuring frequency
Median frequency detected: 2.496610 GHz (917 samples out of 1000). 
129996 129996 
basic_decoder timing: 1.824 nanoseconds per set bit 
simdjson_decoder timing: 1.294  nanoseconds per set bit  
basic_decoder: 4.553 cycles per set bit 
simdjson_decoder: 3.230 cycles per set bit  
Measuring frequency
Median frequency detected: 2.496610 GHz (969 samples out of 1000). 
129996 129996 
basic_decoder timing: 1.641 nanoseconds per set bit 
simdjson_decoder timing: 1.197  nanoseconds per set bit  
basic_decoder: 4.097 cycles per set bit 
simdjson_decoder: 2.989 cycles per set bit  
Measuring frequency
Median frequency detected: 2.496610 GHz (962 samples out of 1000). 
129996 129996 
basic_decoder timing: 1.633 nanoseconds per set bit 
simdjson_decoder timing: 1.194  nanoseconds per set bit  
basic_decoder: 4.078 cycles per set bit 
simdjson_decoder: 2.980 cycles per set bit  
Measuring frequency
Median frequency detected: 2.496610 GHz (966 samples out of 1000). 
129996 129996 
basic_decoder timing: 1.629 nanoseconds per set bit 
simdjson_decoder timing: 1.189  nanoseconds per set bit  
basic_decoder: 4.068 cycles per set bit 
simdjson_decoder: 2.970 cycles per set bit  
Measuring frequency
Median frequency detected: 2.496610 GHz (950 samples out of 1000). 
129996 129996 
basic_decoder timing: 1.652 nanoseconds per set bit 
simdjson_decoder timing: 1.180  nanoseconds per set bit  
basic_decoder: 4.125 cycles per set bit 
simdjson_decoder: 2.947 cycles per set bit  
Measuring frequency
Median frequency detected: 2.496610 GHz (968 samples out of 1000). 
129996 129996 
basic_decoder timing: 1.655 nanoseconds per set bit 
simdjson_decoder timing: 1.203  nanoseconds per set bit  
basic_decoder: 4.131 cycles per set bit 
simdjson_decoder: 3.003 cycles per set bit  
Measuring frequency
Median frequency detected: 2.496610 GHz (967 samples out of 1000). 
129996 129996 
basic_decoder timing: 1.648 nanoseconds per set bit 
simdjson_decoder timing: 1.174  nanoseconds per set bit  
basic_decoder: 4.114 cycles per set bit 
simdjson_decoder: 2.932 cycles per set bit  


```

The Apple A12 has seemingly a rated frequency of 2.5GHz. So these nanoseconds translate into about 4.3 and 3.0 cycles per set bit. For comparison, an Intel Skylake get 4.7	and	3.4 cycles per set bit.



## Credit


The app. reuses code by Benoît Maison.
