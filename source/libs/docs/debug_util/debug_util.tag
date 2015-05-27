<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>debug.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/debug_util/</path>
    <filename>a00001</filename>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_UTIL_BUFFER_SIZE</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a6157e03a309e5738d19f281c7d260b4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_UTIL_TRACE</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a6b158bcfd4ad0e669a9f74d0235bdc03</anchor>
      <arglist>(level, format,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_UTIL_DEBUG</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>af4439bbbf7808aa4608088c5fc8762e6</anchor>
      <arglist>(level, format,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_UTIL_ERROR</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a129eccb79d3579b55a92eeed8c6d2660</anchor>
      <arglist>(level, format,...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEBUG_UTIL_TRACE_ELEMENT</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a6a89ca9ad50e359c09f5bed6858297c3</anchor>
      <arglist>(level, element, function)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>debug_util_TRACE_FUNTION</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>aea1a1da48f9be116b8ec308d8bc29b76</anchor>
      <arglist>)(const char *)</arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>debug_util_ELEMENT_TRACE_FUNTION</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>acb797b3ccc582e3330d3cf3e761b3616</anchor>
      <arglist>)(void *element, char buffer[DEBUG_UTIL_BUFFER_SIZE])</arglist>
    </member>
    <member kind="enumeration">
      <name>debug_util_LEVELS</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>aa67647dffda81c4bf40a22606de434db</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_UTIL_LEVEL_NONE</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>aa67647dffda81c4bf40a22606de434dba5d2e193de4fef2db09055144384e6c29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_UTIL_LEVEL_TRACE</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>aa67647dffda81c4bf40a22606de434dba8cfdc9de8fc139c9bcc40ef2324f1547</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_UTIL_LEVEL_DEBUG</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>aa67647dffda81c4bf40a22606de434dba6063a46d3dacfc5c0352f90d38621342</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DEBUG_UTIL_LEVEL_ERROR</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>aa67647dffda81c4bf40a22606de434dbab9f2453beabe40f7737958371fdaa120</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>debug_util_set_trace_function</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>ab0003a6a8fd130a4b50ac633f6bf3e6e</anchor>
      <arglist>(debug_util_TRACE_FUNTION trace)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>debug_util_set_level</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>ab013a5a2e9972c0c09a0bba4baccaeaf</anchor>
      <arglist>(const debug_util_LEVELS level)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>debug_util_trace</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a3c7765ea1964ef3f9afa6fc919b58196</anchor>
      <arglist>(unsigned level, const char *file, unsigned line, const char *format,...)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>debug_util_trace_element</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>adcc77339ec3396c54a56cae414e4866e</anchor>
      <arglist>(unsigned level, const char *file, unsigned line, void *element, debug_util_ELEMENT_TRACE_FUNTION function)</arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/include/debug_util/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/debug_util/</path>
    <filename>dir_7a51f80646919a944c604289543ef574.html</filename>
    <file>debug.h</file>
    <file>debug_utilconfig.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/include/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/</path>
    <filename>dir_4d47a3359d3b6180483f780da6526630.html</filename>
    <dir>/home/elesd/programing/github/smart_hrir/source/libs/include/debug_util/</dir>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/</path>
    <filename>dir_6719ab1f1f7655efc2fa43f7eb574fd1.html</filename>
    <dir>/home/elesd/programing/github/smart_hrir/source/libs/include/</dir>
  </compound>
</tagfile>
