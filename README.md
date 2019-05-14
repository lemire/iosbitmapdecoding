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

## Credit


The app. reuses code by Benoît Maison.
