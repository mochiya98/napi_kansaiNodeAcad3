{
  "targets": [
    {
      "target_name": "promise",
      "sources": [ "promise.cc" ],
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
