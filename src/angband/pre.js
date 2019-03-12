function setupFilesystem(){
    FS.mount(IDBFS, {}, '/home/web_user');
}

if(Module == null){
    console.log("There is no Module yet");
}else{
   console.log("There is a module already");
}
