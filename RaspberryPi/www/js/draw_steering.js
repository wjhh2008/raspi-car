var c=document.getElementById("steering");
var cxt=c.getContext("2d");
var pic=new Image();
var picisonload = false;
pic.src="/img/steering.jpg";
//cxt.save();
pic.onload=function(){
	cxt.drawImage(pic,0,0);
	picisonload = true;
	cxt.translate(pic.width/2, pic.height/2);
}
function rou(angle){
	if (!picisonload) return;
	cxt.clearRect(-pic.width/2,-pic.height/2,c.width,c.height);
	cxt.rotate(1.3*angle * Math.PI / 180);
	cxt.drawImage(pic,-pic.width/2,-pic.height/2); 
	cxt.rotate(-1.3*angle * Math.PI / 180); 
}
