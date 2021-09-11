# TiggerRGB



## Background

I’m recently into playing with Eurorack modules and come to the point where I wanted to build my own. I’ve played with Arduino and other microcontroller projects for a while, so I decided to make this trigger-controlled RGB. The RGB trail effect was inspired by Dave’s Garage’s YouTube [video](https://www.youtube.com/watch?v=yM5dY7K2KHM&list=PLF2KJ6Gy3cZ7ynsp8s4tnqEFmY15CKhmH&index=10) on the comet effec and the code that he wrote. [Dave's GitHub Link](https://github.com/davepl/DavesGarageLEDSeries).

Special thanks, Dave, for inspiring and helping a kid on the other side of the globe!

## About the code

The current version of the code utilizing the FastLED library. There are two trigger inputs and two analog inputs. Out of the two analog inputs, I only used one to control the decaying speed of the lights. Feel free to take a look and build your own test circuit.

I also included a PCB design I made in KiCad. After receiving the PCBs and soldering the parts, I was able to get the entire prototype mounted on the back of a blank panel (10HP). [Here’s a demo video.](https://www.bilibili.com/video/BV1xv411P731?share_source=copy_web)

