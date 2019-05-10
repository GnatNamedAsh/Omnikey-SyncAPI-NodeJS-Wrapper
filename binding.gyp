{
    "targets": [{
        "target_name": "Smartcard",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "Stuff/main.cpp",
            "Stuff/SmartcardWrap.cpp",
            "Stuff/SmartcardClass.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [
            "-l<(module_root_dir)/Stuff/Lib/scardsynx64.lib"
        ],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}