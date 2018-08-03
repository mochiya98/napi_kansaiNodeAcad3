{
  "targets": [
    {
      "target_name": "hello",
      "sources": [ "hello.cc" ],
      "conditions": [
        ["OS == \"win\"", {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "AdditionalOptions": ["/source-charset:utf-8"]
            }
          }
        }]
      ]
    }
  ]
}
