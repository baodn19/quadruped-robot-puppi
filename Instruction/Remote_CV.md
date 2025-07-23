# Using MobaXTerm: 
- Install and follow the video instructions to get used to the UI: https://www.youtube.com/watch?v=s7xNGyG9GVc&t
- Run the code after SSH into the device

# Procedure for using cmd:
1. SSH into device with MobaXTerm
2. In MobaXTerm: run `echo $DISPLAY` and note the value after "localhost" (let's call it *dis*)
3. SSH into device with command prompt
4. Run `export DISPLAY=<dis>`
5. Run the code