#!/usr/bin/env node

import path from "path";
import fs from 'fs'
import {   GetConfig, WebView2Config } from "./build_tool_cls.mjs";
import { fileURLToPath } from "url";

/**
 * 
 * @param {string} target 
 * @returns 
 */
function getDistBinPath(target){ 
    var curFile =  path.dirname(fileURLToPath( import.meta.url)); 
    var binFolder =  path.join(curFile,"dist_bin");

    if(target == "x64"){
        return path.join(binFolder,"x64")
    }

    return path.join(binFolder,"Win32");
}


class FromTo{
    from = "";
    to = "";
}

/**
 * 
 * @param {WebView2Config} wConfig 
 */
function copyExe(wConfig){ 
    var sourceFolder = getDistBinPath(wConfig.target);

    /**
     * @type {FromTo[]}
     */
    var listFile = [
        { from : "CmdWebview2.exe" , to : wConfig.appname+".exe" },
        { from : "WebView2Loader.dll" , to : null },
    ]
 
    fs.mkdirSync(wConfig.outputfolder,{recursive :true});

    for(var item of listFile){

        if(!item.to){
            item.to = item.from;
        }

        item.from =  path.join(sourceFolder, item.from);
        item.to = path.join(wConfig.outputfolder,item.to);

        console.log(item); 
        fs.copyFileSync(item.from,item.to);

    }
}


function buildWebView2(){
    var jsn = GetConfig();
    copyExe(jsn);
}

buildWebView2();