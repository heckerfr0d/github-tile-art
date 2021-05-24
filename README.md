
# GitHub Tile Art

A Qt C++ app to customize your GitHub contribution graph. Basically a C++ port of [this python GUI app](https://github.com/heckerfr0d/github-abuz).  
  
## Instructions

### Usage

![screenshot](resources/screenshot.png)  

The `auto-update` feature stores your designs for the `auto-update` script to automatically select and set one (from all your default year designs) on startup.  
**Warning:** Only do this on a dedicated repo as it will delete and recreate the repo. Only the commits made for other years with `Auto Update?` checked remain unaffected.  
The rest is pretty self-explanatory (I think :p).  
Username, password and email must be the ones corresponding to your github account.  
Link to repo must be the https link. 100% recommend creating a dedicated repo for this :p .  
You can make your design using the grid of checkboxes. You can also translate text directly to tile art. Current build only supports caps and some special characters :grimacing: .  
`Invert` behaves exactly as expected.  
You can select under which year you want your graffiti to appear. It defaults to the last 52 weeks which is what your profile page normally displays.  
Commits per day is, obviously, the number of commits you want the program to do per day. The tile gets darker according to this number.  
Once you're satisfied with the design (are we ever? :P), Just tell the app to `Do IT` and it will :relieved: .  
**Note:** Depending on the number of commits it may take some time and the app may appear to not respond but don't worry, it's just creating all those commits in the background :grin: .  

### Build

README is still WIP, check back later for the build process 😁
