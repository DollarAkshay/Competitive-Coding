$s=join"",A..Z,a..z,0..9,"+/A";
for(<>,<>;<>;<>)
{
$_= ~~reverse;
$r=0,$i=0;
for(/./g){
$x=index($s,$_);
$r+=$i++%2?$x:$x<32?$x*2:2*$x%64+1
}
print substr($s,64-$r%64,1).$/
}