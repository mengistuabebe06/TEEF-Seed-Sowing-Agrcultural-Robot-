<?php

require_once 'connect.php'; 
//mysql_select_db("$db_name")or die("cannot select DB");
$sql = "select * from farmlandcoverage"; 
$result = mysqli_query($conn,$sql);
$json = array();
 
if(mysqli_num_rows($result)){
while($row=mysqli_fetch_assoc($result)){
$json['emp_info'][]=$row;
 }
}
mysqli_close($conn);
echo json_encode($json);
?>