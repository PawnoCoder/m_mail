<?php
	/*
	
		About: Mail include v2.1
		Author: Noname
		
	*/
	
	$to = $_POST['to'];
	$subject = iconv("cp1251", "utf-8", $_POST['subject']);
	$message = iconv("cp1251", "utf-8", $_POST['message']);
	$additional_headers = iconv("cp1251", "utf-8", $_POST['additional_headers']);
	$additional_parameters = $_POST['additional_parameters'];
	$type = $_POST['type'];
	
	if (is_null($to) || is_null($subject) || is_null($message) || is_null($additional_headers) || is_null($additional_parameters))
		die('Error: Missing parameters.');
	
	$headers = "From: $additional_headers <$additional_parameters>"
		. "\r\n" . "Reply-To: $additional_headers"
		. "\r\n" . "X-Mailer: PHP/" . phpversion();
		
	if ($type == 1)
		$headers .= "\r\n" . "Content-type: text/html";
	
	mail($to, $subject, $message, $headers);
?>