{
  'targets': [
    {
      'target_name': 'validation',
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'dependencies': [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ]
      'cflags_cc!': [ '-fno-exceptions' ],
      'cflags!': [ 
        '-O3',
         '-fno-exceptions'
      ],
      'cflags': [ '-O2' ],
      'sources': [ 'src/validation.cc' ],
      'conditions': [
        ['OS=="win"', {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": 1
            }
          }
        }],
        ['OS=="mac"', {
          "xcode_settings": {
            "CLANG_CXX_LIBRARY": "libc++",
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'MACOSX_DEPLOYMENT_TARGET': '10.7'
          }
        }]
      ]
    },
    {
      'target_name': 'bufferutil',
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'cflags!': [ 
        '-O3',
         '-fno-exceptions'
      ],
      'cflags': [ '-O2' ],
      'sources': [ 'src/bufferutil.cc' ],
      'conditions': [
        ['OS=="win"', {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": 1
            }
          }
        }],
        ['OS=="mac"', {
          "xcode_settings": {
            "CLANG_CXX_LIBRARY": "libc++",
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'MACOSX_DEPLOYMENT_TARGET': '10.7'
          }
        }]
      ]
    }
  ]
}
