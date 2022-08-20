# OpenGoLf
<p>7/28/22 CAS Reflection 3 - OpenGoLf </p>

<h1> How to download and execute </h1>
<p> <b> Note about source code: </b> the irrKlang dlls are not included in the /golf folder due to them being architecture dependant. Thus, if you want to run the source code yourself, drag the respective dlls from the /standalone folder into the /golf folder where main.cpp resides </p>
<p> <b> This program requires you to be using MSVC (Visual Studio). </b> I use VS2022, but older versions may work. This project uses C++20. <br /> 
  To download, install git if not already installed and type the following command in any terminal: </p>

```
git clone https://github.com/dec-lied/OpenGoLf.git
``` 

<p> to download the repository. The main code is in the golf/ directory with the includes being in the include/ directory. You can do either of the following to run the 
program: </p>
<ol>
  <li> Build it from the source yourself by opening golf.sln and selecting Release as well as x64 or x86 according to your pc architecture then click build.
       If you decide to do this, be sure to <b> <ins> place the executable golf.exe into the /standalone folder and pull the architecture respective dlls from the dll folders into the /standalone folder along with golf.exe. </ins> </b> </li>
  <li> Download the release according to your comuter's architecture from the Releases tab on 
  <a href="https://github.com/dec-lied/OpenGoLf/releases/tag/V2.0"> this page </a>. </li>
</ol>

<h1> How to play </h1>
<ul>
  <li> Click Q, W, E, and R to switch your shot's power. Q is the lowest, R is the highest power, and W and E are in the middle respectively. You can see your current
  power in the bottom left meter or by the dotted line's length. </li>
  <li> The rotating dotted line indicates your shot's path. It is not representative of the shot's distance, or that would be too easy, just direction. You can shoot 
  with the mouse's left click or by pressing the space bar. </li>
  <li> Try to get the ball into the hole in any amount of shots. The ball bounces off of the walls and obstacles, try to win in the least amount of strokes! </li>
  <li> After getting the ball into the hole, it will advance to the next level. </li>
  <li> Press the Escape key to exit the game at any point. </li>
</ul>

<h1> Disclaimer </h1>
<p> In having a friend test the game, the collision detection was not working as intended on their pc. I am looking into the issue, but hopefull it works on your end </p>

<h1> Screenshots of the game </h1>

![lv2](https://user-images.githubusercontent.com/103293120/181620581-97e0de1e-3c1f-4697-b30d-5eb141d39aa3.png)
![lv3](https://user-images.githubusercontent.com/103293120/181620585-4855065a-16ec-40d1-956c-a908eeedc512.png)
![lv4](https://user-images.githubusercontent.com/103293120/181620595-18feb7ec-abfe-43e4-971d-a937201975dd.png)
