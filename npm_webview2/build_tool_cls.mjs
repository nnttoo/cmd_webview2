
import path from "path";
import fs from 'fs'

export class WebView2Config {
    appname = "NpmWebView2";
    outputfolder = "./dist";
    target = "Win32"
}

export function GetConfig(){
    
    /** @type {WebView2Config | null} */
    var config = null;
    
    try {
        var file = fs.readFileSync("./npm_webview2.json",{}).toString();
        config = JSON.parse(file);

    } catch (error) {
        console.log(error);
    }
 
    var configCls = new WebView2Config();
    if(config != null){

        Object.assign(configCls,config);
    }

    return configCls;
}
 