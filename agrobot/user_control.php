<?php

include_once 'connection.php';
	
	class User {
		
		private $db;
		private $connection;
		
		function __construct() {
			$this -> db = new DB_Connection();
			$this -> connection = $this->db->getConnection();
		}
		
		public function does_user_exist($username,$password)
		{
			$query = "Select * from user where UserName='$username' and Password = '$password' ";
			$result = mysqli_query($this->connection, $query);
			if(mysqli_num_rows($result)>0){
				$json['success'] = ' Welcome '.$username;
				echo json_encode($json);
				mysqli_close($this -> connection);
			}else{
				//$query = "insert into user (UserName, Password) values ( '$username','$password')";
				//$inserted = mysqli_query($this -> connection, $query);
				//if($inserted == 1 ){
					//$json['success'] = 'Acount created';
				//}else{
					$json['error'] = 'Wrong password';
				//}
				echo json_encode($json);
				mysqli_close($this->connection);
			}
			
		}
		
	}
	
	
	$user = new User();
	if(isset($_POST['username'],$_POST['password'])) {
		$username = $_POST['username'];
		$password = $_POST['password'];
		
		if(!empty($username) && !empty($password)){
			
			$encrypted_password = md5($password);
			$user-> does_user_exist($username,$password);
			
		}else{
			echo json_encode("you must type both inputs");
		}
		
	}














?>
