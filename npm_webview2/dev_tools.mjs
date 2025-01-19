#!/bin/env node

import { copyFolder } from "./build_tool_cls.mjs";

function copyFolder(src, dest) {
    // Cek apakah folder tujuan sudah ada, jika belum buat foldernya
    if (!fs.existsSync(dest)) {
        fs.mkdirSync(dest, { recursive: true });
    }

    // Baca semua file dan folder di dalam folder sumber
    const items = fs.readdirSync(src);

    items.forEach(item => {
        const srcPath = path.join(src, item);
        const destPath = path.join(dest, item);

        const stat = fs.statSync(srcPath);

        // Jika item adalah folder, panggil fungsi ini lagi secara rekursif
        if (stat.isDirectory()) {
            copyFolder(srcPath, destPath);
        } else {
            // Jika item adalah file, salin file tersebut
            fs.copyFileSync(srcPath, destPath);
        }
    });
}


function copyBin() {
    var win32Folder = "../win32/CmdWebview2/bin/Release/";

    var win32DistBin = "./dist_bin/";

    copyFolder(win32Folder, win32DistBin);
}

copyBin();