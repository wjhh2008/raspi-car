var count=0;
var a=0;	//0-4000  0-2000:backward 2000-4000:forward
var b=150;	//50-250
var direction=0;
var note=document.getElementById("doEvent");
var tiltLR,tiltFB,dir;
var level=0,old_level=0,step=4;
var pow=0,old_pow=0;
var forward = 0;
var change=0;
init();
function gogogo(eventData){
	tiltLR=Math.round(eventData.gamma);
	tiltFB=Math.round(eventData.beta);
	dir=Math.round(eventData.alpha);
	//deviceOrientationHandler(tiltLR,tiltFB,dir);
	
	//sendcmd();
	if (Math.round(tiltLR)<0){
		if (direction!=0){
			direction = 0;
			note.innerHTML="Up Side Down!";
			note.style.color="red";
		}
	}else{
		if (direction!=1){
			note.innerHTML="GOGOGO!";
			note.style.color="black";
			direction = 1;
		}
	
		if (Math.abs(tiltFB)<40)
			level = Math.round(-tiltFB/step);
		forward = 90-tiltLR;
		if (Math.abs(forward)>60) forward = forward>0?60:-60;
		pow=Math.abs(forward)*10/6;
		//document.getElementById("test").innerHTML=level;
		//change=0;
		if (level!=old_level){
			rou(level*step);
			old_level = level;
		}
		draw_p(pow/10);
		
		a=Math.round(forward*255/60); 
		b=-tiltFB+90;
		//document.getElementById("test").innerHTML=""+a+b;
	}
}
function init(){
	if(window.DeviceOrientationEvent){
		note.innerHTML="Let's Rock!";
		window.addEventListener('deviceorientation',gogogo,false);
	}
	else{
		document.getElementById("doEvent").innerHTML="Not supported on your device or browser.  Sorry."
	}
}
/*
function deviceOrientationHandler(tiltLR,tiltFB,dir){
	document.getElementById("doTiltLR").innerHTML=tiltLR;
	document.getElementById("doTiltFB").innerHTML=tiltFB;
	document.getElementById("doDirection").innerHTML=dir;
}
*/

function sendcmd(){
	if (direction==1){
		xmlhttp.open("GET","/go.py?motor="+a+"&servo="+b,true);
		xmlhttp.send();
	}
}
setInterval(sendcmd,100)
	
