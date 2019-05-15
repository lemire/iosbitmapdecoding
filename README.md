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

## Sample result

iPhone XR, Xcode 10.1
```
129996 129996 
basic_decoder time 45.938914 nanoseconds per set bit 
simdjson_decoder time 11.339772  nanoseconds per set bit  
129996 129996 
basic_decoder time 15.304638 nanoseconds per set bit 
simdjson_decoder time 11.169254  nanoseconds per set bit  
129996 129996 
basic_decoder time 14.227681 nanoseconds per set bit 
simdjson_decoder time 10.192621  nanoseconds per set bit  
129996 129996 
basic_decoder time 9.827546 nanoseconds per set bit 
simdjson_decoder time 7.529719  nanoseconds per set bit  
129996 129996 
basic_decoder time 9.522729 nanoseconds per set bit 
simdjson_decoder time 7.445742  nanoseconds per set bit  
129996 129996 
basic_decoder time 9.461830 nanoseconds per set bit 
simdjson_decoder time 7.417536  nanoseconds per set bit  
129996 129996 
basic_decoder time 9.493561 nanoseconds per set bit 
simdjson_decoder time 7.439652  nanoseconds per set bit  
129996 129996 
basic_decoder time 9.995500 nanoseconds per set bit 
simdjson_decoder time 5.838000  nanoseconds per set bit  
129996 129996 
basic_decoder time 7.306956 nanoseconds per set bit 
simdjson_decoder time 5.705624  nanoseconds per set bit  
129996 129996 
basic_decoder time 7.095731 nanoseconds per set bit 
simdjson_decoder time 5.920374  nanoseconds per set bit  
```

The Apple A12 has seemingly a rated frequency of 2.5GHz. So these nanoseconds translate into about 18 and 15 cycles per set bit.



## Credit


The app. reuses code by Benoît Maison.
