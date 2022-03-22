<?php

//if ($_SERVER['REQUEST_METHOD']=='POST') {
    
    $id = 1;

    require_once 'connect.php';

    $sql = "SELECT * FROM sensorvalue WHERE SensorID='$id' ";

    $response = mysqli_query($conn, $sql);

   // $result = array();
   // $result['read'] = array();

   // if( mysqli_num_rows($response) === 1 ) {
        
       // if ($row = mysqli_fetch_assoc($response)) {
 
            // $h['SeedLevel']        = $row['SeedLevel'] ;
            // $h['Position']       = $row['Position'] ;
 
            // array_push($result["read"], $h);
 
           //  $result["success"] = "1";
            // echo json_encode($result);
        //}
 
  // }
  $emparray = array();
 while($row =mysqli_fetch_assoc($response))
    {
       $temp = [
		'SeedLevel'=>$row["SeedLevel"],
		
	];
	array_push($emparray,$temp);
    }
   echo json_encode($emparray);
 //else {
 
    // $result["success"] = "0";
     //$result["message"] = "Error!";
     //echo json_encode($result);
     mysqli_close($conn);
      //}
 
 ?>