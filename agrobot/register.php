<?php

//if ($_SERVER['REQUEST_METHOD'] =='POST'){

    $Fname = $_POST['Fname'];
    $Lname = $_POST['Lname'];
	$Username = $_POST['Username'];
    $Email = $_POST['Email'];
    $Password = $_POST['Password'];
	
	$PhoneNumber = $_POST['PhoneNumber'];
	

    //$passwordd = password_hash($password, PASSWORD_DEFAULT);

    require_once 'connect.php';
	$query = mysqli_query($conn,"SELECT * FROM user WHERE PhoneNumber = '$PhoneNumber'");
    $num = mysqli_num_rows($query);
    if($num > 0){
    echo "User already exists";
	}
	else{
		$sql = "INSERT INTO user (FirstName,LastName,UserName,Email,Password,PhoneNumber) VALUES ('$Fname','$Lname','$Username','$Email','$Password','$PhoneNumber')";
 
    if ( mysqli_query($conn, $sql) ) {
      // $result["success"] = "1";
      // $result["message"] = "success";

       //echo json_encode($result);
      // mysqli_close($conn);
	  echo "data inserted successfully";

   } else {

       //$result["success"] = "0";
       //$result["message"] = "error";

      //echo json_encode($result);
	  echo "not inserted";
      
	}
	}
   mysqli_close($conn);
//}

?>