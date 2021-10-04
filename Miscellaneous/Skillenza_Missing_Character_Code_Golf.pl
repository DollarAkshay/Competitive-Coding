$s=join"",A..Z,a..z,0..9,"+/A";
for(<>,<>;<>;<>)
{
@a=map{index($s,$_)}/./g;
for(
$r=0,$i=0;
$i<=$#a;
$r+=$i++%2?$x:$x<32?$x*2:2*$x%64+1)
{$x=@a[$#a-$i]}
print substr($s,64-$r%64,1).$/
}