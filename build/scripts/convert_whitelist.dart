import 'dart:io';
import 'dart:convert';

///converts the output from EMTERPRETIFY_ADVISE to a list of strings usable by gn.
///takes one argument being the file to convert.
int main(List<String> args){
  int code = 0;
  if(args.length == 1){
    File whitelist  = new File(args[0]);
    String contents = whitelist.readAsStringSync();
    List<dynamic> whitelistItems = jsonDecode(contents.substring(1,contents.length - 1));
    whitelistItems.forEach((item) => print(item));
  }else{
    print("convert_whitespace requires 1 argument which is the path of a file to convert");
    code =1;
  }
  return code;
}