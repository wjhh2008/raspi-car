var cxt1=document.getElementById("power1").getContext("2d");
for (var i=1;i<10;i++){
	cxt1.moveTo(0,18*i);
	cxt1.lineTo(40,18*i);
}
//cxt1.strokeStyle="#FFFFFF";
cxt1.stroke();


var grd=cxt1.createLinearGradient(0,0,40,180);

grd.addColorStop(0,"#FF0000");
grd.addColorStop("0.5","#FFFF00");
grd.addColorStop(1,"#0066FF");

function draw_p(power){
	if (power>10) power=10;
	if (power<0) power=0;
	cxt1.clearRect(0,0,40,180);
	cxt1.fillStyle=grd;
	cxt1.fillRect(0,0,40,180);
	cxt1.fillStyle="#FFFFFF";
	cxt1.fillRect(0,0,40,(10-power)*18);
	//draw_l();
	cxt1.stroke();
}

//draw_p(10);

