<?php


//if ($_SERVER['REQUEST_METHOD']=='POST') {
   include 'connect.php';
   show();
//}
function show(){
	global $conn;
	$query = "Select * from sensorvalue; ";
	$query2 = "Select * from farmlandcoverage; ";
	$result2 = mysqli_query($conn,$query2);
	$result = mysqli_query($conn,$query);
	$nr = mysqli_num_rows($result);
	$temp = array();
	if( $nr > 0){ 
	
	while($row =mysqli_fetch_assoc($result)){
		$temp[] = $row;
		
	    }
	}
	header('Content-Type: application/json');
	echo json_encode(array("sensorvalue"=>$temp));
	mysqli_close($conn);
}
?>