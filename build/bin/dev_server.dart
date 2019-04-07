import 'dart:io';

/// simple http server, expects build to be in out/browserband
void main(List<String> args) async{
   var server = await HttpServer.bind(
    "localhost",
    8080,
  );
  print('Listening on localhost:${server.port}');

  await for (HttpRequest request in server) {
    print("Request Received -> ${request.requestedUri}");
    File toServe = null;
    if(request.uri.path == "/"){
      toServe = File("web/angband/angband.html");
    }else{
      Directory buildDir = Directory("obj/src/angband");
      String filename = request.uri.pathSegments.last;
      toServe = File("${buildDir.path}/${filename}");
    }
    if(toServe.existsSync()){
      print("Serving - ${toServe.path}");
      List<int> contents = toServe.readAsBytesSync();
      String contentType = toServe.path.split(".").last;
      switch(contentType){
        case 'js':
          request.response.headers
            ..add("Content-Type","text/javascript");
            break;
        case 'html':
          request.response.headers
            ..add("Content-Type","text/html");
            break;
        case 'wasm':
          request.response.headers
            ..add("Content-Type","application/wasm");

      }
      request.response
        ..add(contents)
        ..close();
    }else{
      request.response
        ..statusCode = 404
        ..close();
    }
  }
}