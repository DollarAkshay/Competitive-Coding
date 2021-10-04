@s=(A..Z,a..z,0..9,"+","/","A");
print "String : |@s|\n";
$_="Test";
$_ = 'E';
@res = grep {@s[$_]eq'E'}0..63;
print "Res : |@res|\n"