var count=0;
var a=0;	
var b=0;	
var direction=0;
var note=document.getElementById("doEvent");
var tiltLR,tiltFB,dir;
var level=0,old_level=0,step=4;
var pow=0,old_pow=0;
var spe=new Array(30,60,90);
var lvspe=new Array("Here We GO","Rush","Unbelievable");
var lvsp = 0,old_lv;
var forward = 0;
var change=0;
var id;
var st = 0;
var stt = document.getElementById("start");
var spst = document.getElementById("speed");
function sendcmd(){
	if (direction==1){
		xmlhttp.open("GET","/go.py?motor="+a+"&servo="+b,true);
		xmlhttp.send();
	}
}

init();

//setTimeout("initmod();",1000);

function gogogo(eventData){
	if (st==0) return;
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
		a = 0;
		b = 90;
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
		
		a=Math.round(forward*spe[lvsp]*255/60/90); 
		b=-tiltFB+90;
		//document.getElementById("test").innerHTML=""+a+b;
	}
}
function init(){
	if(window.DeviceOrientationEvent){
		//note.innerHTML="Let's Rock!";
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


function poweroff(){
	clearInterval(id);
	a = 255; b = 255;
	sendcmd();
}
function start(){
	if (st==0){
		a = 2; b = 255;
		sendcmd();
		id = setInterval(sendcmd,100);
		stt.innerHTML="Stop";
		st = 1;
	}else if (st==1){
		a = 0; b = 90;
		sendcmd();
		clearInterval(id);
		
		stt.innerHTML="Start";
		st = 0;
		draw_p(0);
		rou(0);
		note.innerHTML="READY";
	}
}
function cgspeed(){
	lvsp = (lvsp+1) % 2;
	spst.innerHTML = lvsp+1;
}
function nos(){
	old_lv = lvsp;
	lvsp = 2;
	setTimeout("postnos();",2000);
}
function postnos(){
	lvsp = old_lv;
	spst.innerHTML = lvsp+1;
	
}
