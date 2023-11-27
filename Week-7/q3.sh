echo "Enter a command:"
read user_command
echo "Enter the output file name:"
read output_file
$("$user_command" 2>&1 | tee "$output_file")
echo "Output saved to $output_file"