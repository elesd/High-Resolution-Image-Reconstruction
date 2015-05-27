<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>dumper.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</path>
    <filename>a00007</filename>
    <member kind="define">
      <type>#define</type>
      <name>DUMPER_OK</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>a963dec961ab29f9094b3df41dc59916c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DUMPER_FILE_OPEN_ERROR</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>aba952530ea6188d27c47d40d00493dd0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DUMPER_WRITE_ERROR</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>a86903e1939ee148d83c1784423c70f2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DUMPER_TRACE_IMAGE</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>a3186df10cbb082de2b4310c7fa31b21f</anchor>
      <arglist>(data, width, height)</arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>dumper_ERROR_CODE</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>af6536bdd6757c29a21b351fe6f03e9ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>dumper_ERROR_CODE</type>
      <name>dumper_trace_to_file</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>af4f6f8f66f2106a07ff5262b18136350</anchor>
      <arglist>(const char *file_name, const void *data, unsigned length)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>gaussian_filter.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</path>
    <filename>a00008</filename>
    <member kind="function">
      <type>double</type>
      <name>gaussian_filter_calc_with_sigma</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>a316f61d728c11dcb3990199530349adb</anchor>
      <arglist>(const double x, const double y, const double sigma)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gaussian_filter_calc</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>ada1fef0f18b43799dcc82232bf786ad5</anchor>
      <arglist>(const double x, const double y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gaussian_filter_set_sigma</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>ac5f9dcbf038d161db3a68a80657990e4</anchor>
      <arglist>(const double sigma)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>gaussian_filter_get_sigma</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>aae1cf8b3c6e0bd2b8c4f9ade61501421</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>haar_transformation.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</path>
    <filename>a00009</filename>
    <class kind="struct">haar_transformation_DATA_SOURCE</class>
    <member kind="typedef">
      <type>unsigned char *</type>
      <name>haar_transformation_DATA_GRID</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>a15c000e971023d4dd5ea1540870dad05</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>haar_transformation_transform</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>aa12982139c87f77e9d40ba6df5f077db</anchor>
      <arglist>(haar_transformation_DATA_SOURCE data_source)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>haar_transformation_inverse_transformation</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>a78794f57e4b062b9865126cd2efcba6a</anchor>
      <arglist>(haar_transformation_DATA_SOURCE data_source)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>image_amplifier.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</path>
    <filename>a00011</filename>
    <includes id="a00012" name="image_filter.h" local="yes" imported="no">image_filter.h</includes>
    <includes id="a00015" name="non_maxima.h" local="yes" imported="no">non_maxima.h</includes>
    <class kind="struct">image_amplifier_OPTIONS</class>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_AMPLIFIER_OK</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>ad4757f615c82fc0c11ca12509addda11</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_AMPLIFIER_FILTER_ERROR</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>ae436e4b7fc21db27f5839e1ff2f11ad0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_AMPLIFIER_NON_MAXIMA_ERROR</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>afe85512071c88f9b99781422844e8fb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_AMPLIFIER_MEM_ERROR</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a6923f44a0c9d6c9677800a23c957bfa8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>image_amplifier_ERROR_CODE</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a0d1363de9476dc6ae5b800ea4fade103</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>image_amplifier_SCALE_FUNCTION</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a1ea386c90cd9638e2f2576d348eb122f</anchor>
      <arglist>)(const image_filter_FILTER_GRID input, const image_filter_IMG *original, image_filter_IMG *out)</arglist>
    </member>
    <member kind="enumeration">
      <name>image_amplifier_FILTER_TYPE</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>ab9ab1f07cda00e3ff3333457d61d7cca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>image_amplifier_PROCESS_TYPE</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a6409b55393af13a405538b966d80ec1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>image_amplifier_ERROR_CODE</type>
      <name>image_amplifier_details_up</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>ae99654f2d59a77ebcc06fbc4fcb46bf7</anchor>
      <arglist>(const image_filter_IMG *input, const image_amplifier_OPTIONS *options, image_filter_IMG *output)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_amplifier_scale</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a8cf8d5fc4dc72339a2ca0b21d8b6c69e</anchor>
      <arglist>(const image_filter_FILTER_GRID input, const image_filter_IMG *original, image_filter_IMG *out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_amplifier_scale_to_origin</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a7ef6a75724d9ffa2c5aec848895a0be7</anchor>
      <arglist>(const image_filter_FILTER_GRID input, const image_filter_IMG *original, image_filter_IMG *out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_amplifier_avg_scale</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a91adba19c8150ae3cf915e44b814a1e0</anchor>
      <arglist>(const image_filter_FILTER_GRID input, const image_filter_IMG *original, image_filter_IMG *out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_amplifier_cut_scale</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a8fa267e3b217e8fdb4d4b952188f5d7c</anchor>
      <arglist>(const image_filter_FILTER_GRID input, const image_filter_IMG *original, image_filter_IMG *out)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>image_filter.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</path>
    <filename>a00012</filename>
    <class kind="struct">image_filter_FILTER</class>
    <class kind="struct">image_filter_IMG</class>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_FILTER_OK</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>afee468629fc317d9e41e8f704f253254</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_FILTER_FILTER_ERROR</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>aa2ca8faffb84d4737b429c7691d7ae01</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_FILTER_FILTER_TYPE_MASK</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>ae0772f91659a981517bc290e7ecd1b7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_FILTER_FILTER_TYPE_FUNCTION</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a03498a10622965acd722a6121c64b793</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned char</type>
      <name>image_filter_IMG_DATA</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>afbdd6cd26209a0a7c753b951a39160e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>double</type>
      <name>image_filter_MASK_DATA</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a4782d495f3f1d69b311256832dd5dc4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>image_filter_ERROR_CODE</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a82e8ecafbcdb867e945139ffe89f63c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>image_filter_IMG_DATA *</type>
      <name>image_filter_DATA_GRID</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a1505c2ea7ed5ea8156460fa804a43730</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>image_filter_MASK_DATA *</type>
      <name>image_filter_FILTER_GRID</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a3d41ec3c203c47ad7dec21ff55acc883</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>image_filter_MASK_DATA *</type>
      <name>image_filter_MASK_GRID</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a8249e3d997dddbfdce6ef81c25b1f3b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>image_filter_MASK_DATA(*</type>
      <name>image_filter_FILTER_FUNCTION</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>acaed2c22ba7a7ae3c91fd6a6acb5b19a</anchor>
      <arglist>)(const image_filter_IMG_DATA img_data, const double x, const double y, const unsigned size)</arglist>
    </member>
    <member kind="typedef">
      <type>image_filter_MASK_DATA(*</type>
      <name>image_filter_MASK_FUNCTION</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a870dae88660f8c99b3ffeb9a440e78e2</anchor>
      <arglist>)(const double x, const double y)</arglist>
    </member>
    <member kind="enumeration">
      <name>image_filter_MODE</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>abecdf477ce7aa2bb6f4b6b0f218a9eea</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>image_filter_ERROR_CODE</type>
      <name>image_filter_apply_filter</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a67aae70446c59e40f48107bbf7a86202</anchor>
      <arglist>(const image_filter_IMG *img, const image_filter_FILTER *filter, image_filter_FILTER_GRID out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_filter_create_image</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a80e8ffd950b89c44cc362bea62e76d91</anchor>
      <arglist>(const unsigned width, const unsigned height, image_filter_IMG *out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_filter_create_filter_by_mask</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>aca91506fce47f276e33c01ee1a619825</anchor>
      <arglist>(const unsigned size, image_filter_MASK_GRID mask, image_filter_FILTER *out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_filter_create_filter_by_function</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>aa7b441e45e2b04ed993b8e75a69dfb50</anchor>
      <arglist>(const unsigned size, image_filter_MASK_FUNCTION mask, image_filter_FILTER *out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_filter_create_filter_function</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a83e83866ae0fd0cee569b15800fc779e</anchor>
      <arglist>(const unsigned size, image_filter_FILTER_FUNCTION filter, image_filter_FILTER *out)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_filter_destroy_filter</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a2e8e2ff324fd37f6f71d35ef6c2f0d26</anchor>
      <arglist>(image_filter_FILTER *filter)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_filter_destroy_image</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>aba9dc1def7d34f75e0f9dbd7029eeb9a</anchor>
      <arglist>(image_filter_IMG *img)</arglist>
    </member>
    <member kind="function">
      <type>image_filter_IMG</type>
      <name>image_filter_copy</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a69c4a25547866f04fdf558a03b8ffcdf</anchor>
      <arglist>(const image_filter_IMG *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_filter_copy_to</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a52b47e76b74ddefe45ecfd3efbc54a8b</anchor>
      <arglist>(image_filter_IMG *dest, const image_filter_IMG *const element)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>image_reconstruct.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</path>
    <filename>a00013</filename>
    <includes id="a00012" name="image_filter.h" local="yes" imported="no">image_filter.h</includes>
    <class kind="struct">image_reconstruct_PARAMETERS</class>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_RECONSTRUCT_OK</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a5d3e11bd9c9b216b7b19bd842ef654ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_RECONSTRUCT_APPROX_ERROR</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a52a36b669da74ad6d52f3879879b37fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_RECONSTRUCT_INVALID_FILTER</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a9a3201c26690e3b1784471c3597ed111</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_RECONSTRUCT_INVALID_SCALE</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>abb31cd9e335e681f67536b4b7424fa99</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_RECONSTRUCT_PREPARATION_ERROR</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>aed253771c228720c23e0ce46c777b561</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_RECONSTRUCT_MEM_ERROR</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a1c03d3ba5b3e6e762312da626f27927b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_RECONSTRUCT_MAX_PIXEL_VALUE</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>abf3443d93974425a774dff64cbfbcdc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMAGE_RECONSTRUCT_DIFF_FUNC</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>acd563962a2519e1a0f6db482b702e0f1</anchor>
      <arglist>(x, y)</arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>image_reconstruct_ERROR_CODE</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a503a55637040f4b6244d1a6bee6c9f01</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>image_reconstruct_NON_MAXIMA_FILTER_TYPE</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a426aaaa85fc93215c39f26d2738b9d87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IMAGE_RECONSTRUCT_SOBEL</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a426aaaa85fc93215c39f26d2738b9d87a6a8e1dbe0cc314b132f2e2706daede1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IMAGE_RECONSTRUCT_PREWIT</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a426aaaa85fc93215c39f26d2738b9d87aa75a25d707f494be996cc5e1f25161cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>image_reconstruct_SCALE_METHOD</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ac27dbc8bff5d1fdaa463a1c1448e134b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IMAGE_RECONSTRUCT_SCALE_TO_ORIGIN</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ac27dbc8bff5d1fdaa463a1c1448e134ba5e1954dcfb78ec0f8f2e922e86201606</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IMAGE_RECONSTRUCT_SCALE_UP</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ac27dbc8bff5d1fdaa463a1c1448e134baa13c9e41d04d587b38ccd22a5537287d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IMAGE_RECONSTRUCT_SCALE_CUT</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ac27dbc8bff5d1fdaa463a1c1448e134baf2ecc0b3d9e21790477928798352fc22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IMAGE_RECONSTRUCT_SCALE_AVG</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ac27dbc8bff5d1fdaa463a1c1448e134ba29162400adfc3650c6ab2e0631e99f66</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IMAGE_RECONSTRUCT_NUM_OF_SCALE_METHOD</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ac27dbc8bff5d1fdaa463a1c1448e134ba74e9c7ac1cbad8c77f4fa1254dda8875</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>image_reconstruct_PREPROCESS_TYPE</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ac74b45c91f9169f8834162f730054133</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IMAGE_RECONSTRUCT_NON_MAXIMA</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ac74b45c91f9169f8834162f730054133a317f8a8322a6c33d2484074f7fdcaf6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IMAGE_RECONSTRUCT_MEDIAN</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ac74b45c91f9169f8834162f730054133ac78b834cacb432cfd12c90c5c75a046a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IMAGE_RECONSTRUCT_GAUSSIAN</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ac74b45c91f9169f8834162f730054133a86ec104c82721cc77e8da13251cc8aee</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>image_reconstruct_ERROR_CODE</type>
      <name>image_reconstruct_calculate_mse</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a82d8843b3a27e1edc2bf9ecfa9460341</anchor>
      <arglist>(const image_filter_IMG *original, const image_reconstruct_PARAMETERS *params, image_filter_IMG *result, unsigned *mse, double *psnr)</arglist>
    </member>
    <member kind="function">
      <type>image_reconstruct_ERROR_CODE</type>
      <name>image_reconstruct_from_lower_image</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a12bf63d8952ea0200b447f80e1f0eecd</anchor>
      <arglist>(const image_filter_IMG *original, const image_reconstruct_PARAMETERS *params, image_filter_IMG *result)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>image_reconstruct_trace_parameter</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>afb80bc758491d33d1398244a6b572d0e</anchor>
      <arglist>(void *parameter, char buffer[DEBUG_UTIL_BUFFER_SIZE])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>median_filter.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</path>
    <filename>a00014</filename>
    <includes id="a00012" name="image_filter.h" local="no" imported="no">image_filter.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MEDIAN_FILTER_MAX_FILTER_SIZE</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>ace98891b151f770abd5067a5a7b2e0da</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>median_filter_apply_filter</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>ab42b1bfcdb2322e7c78deb898822bc57</anchor>
      <arglist>(const image_filter_IMG_DATA img_data, const double x, const double y, const unsigned size)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>non_maxima.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</path>
    <filename>a00015</filename>
    <member kind="define">
      <type>#define</type>
      <name>NON_MAXIMA_WINDOW_SIZE</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>a954ca9bc6ed395484b8f107ab58cd4fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NON_MAXIMA_PREWITT_GRADIENT_MASK</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>afb7e961811a547dd26ea3253951d16a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NON_MAXIMA_SOBEL_GRADIENT_MASK</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>a9bd4bb9ae8e0c43311ca780ab05cfcea</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned char *</type>
      <name>non_maxima_DATA_GRID</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>a5b3067f5dc305f04d5a7958013212c82</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int *</type>
      <name>non_maxima_GRAD_GRID</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>ac46b96fbfbaedf0343eb3282eccb96e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>non_maxima_GRADIENT_MASK</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>a7dd815a0a3b2d6f876ff33571eb2e12d</anchor>
      <arglist>[NON_MAXIMA_WINDOW_SIZE *3]</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>non_maxima_init_data_grid</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>a919db0cf42f0d4598ab90ca27225b3cd</anchor>
      <arglist>(non_maxima_DATA_GRID *data, unsigned int size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>non_maxima_init_grad_grid</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>a1cbba4fe538a208427941a14119e30e0</anchor>
      <arglist>(non_maxima_GRAD_GRID *data, unsigned int size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>non_maxima_destroy_data_grid</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>a6eaea8cb64fc725f55711fefe7e898d5</anchor>
      <arglist>(non_maxima_DATA_GRID data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>non_maxima_destroy_grad_grid</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>ab8e1a180bb41eb19cf535a500c74496b</anchor>
      <arglist>(non_maxima_GRAD_GRID data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>non_maxima_process_image</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>ab71ee6258c81f473f8d88203ebce5eef</anchor>
      <arglist>(const non_maxima_DATA_GRID input, const non_maxima_GRADIENT_MASK mask, const unsigned int size_x, const unsigned int size_y, non_maxima_DATA_GRID output)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>non_maxima_process_image_with_grad_map</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>a46fba296ce8cf4724fccbb1040cfa8c3</anchor>
      <arglist>(const non_maxima_DATA_GRID input, const non_maxima_GRADIENT_MASK mask, const unsigned int size_x, const unsigned int size_y, non_maxima_DATA_GRID output, non_maxima_GRAD_GRID grad_mag_map)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>percent_calculator.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</path>
    <filename>a00016</filename>
    <class kind="struct">percent_calculator_CALCULATOR</class>
    <member kind="function">
      <type>float</type>
      <name>percent_calculator_calc</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a95a56d93980e355a86521f960320aa34</anchor>
      <arglist>(const int act_value, const percent_calculator_CALCULATOR calc)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>haar_transformation_DATA_SOURCE</name>
    <filename>a00001.html</filename>
    <member kind="variable">
      <type>unsigned</type>
      <name>width</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a5a1fcebbd5511855a4fb6c0562799a62</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>height</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a19602f03626b3fa6057df5c682da07bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>haar_transformation_DATA_GRID</type>
      <name>original_image</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a203562228c38ad021a474ea532e5dc4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>haar_transformation_DATA_GRID</type>
      <name>avg_image</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a7c9cba7121efaf248e28958aff45dee6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>haar_transformation_DATA_GRID</type>
      <name>vertical_edges</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a33ea3d2963d128108e2273f3d2de151d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>haar_transformation_DATA_GRID</type>
      <name>horizontal_edges</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>ae9a30f00b69fe14e3617c94cb1c2cf1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>haar_transformation_DATA_GRID</type>
      <name>diagonal_edges</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a6ebe476a92a4970ecf7b1e240298ebe1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>image_amplifier_OPTIONS</name>
    <filename>a00002.html</filename>
    <member kind="variable">
      <type>union image_amplifier_OPTIONS::@0</type>
      <name>params</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>ac7c75806a264a52c487659515f68ff31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct image_amplifier_OPTIONS::@0::@1</type>
      <name>gaussian</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a0811dfec2e3861a8e1f5504baad2c969</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>sigma</name>
      <anchorfile>a00019.html</anchorfile>
      <anchor>a787633e502cc7ef1218ea47aad5fda66</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct image_amplifier_OPTIONS::@0::@2</type>
      <name>non_maxima</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>ad7eecf0d6ca571fa6a35dbab251da362</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>non_maxima_GRADIENT_MASK</type>
      <name>mask</name>
      <anchorfile>a00020.html</anchorfile>
      <anchor>a8e2176fb41c218e74f72dc2bc5cf8658</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_amplifier_FILTER_TYPE</type>
      <name>type</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a4bc5ec751e2e2013dafc3a6b65e24323</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_amplifier_PROCESS_TYPE</type>
      <name>method</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>aa6925bbe38cfca63e79e7d2ea8847396</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>filter_size</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>aa81fa5511538092f08167cbd38091c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_amplifier_SCALE_FUNCTION</type>
      <name>scale</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a9b180d0032ef65ead5962c570736e423</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>image_filter_FILTER</name>
    <filename>a00003.html</filename>
    <member kind="variable">
      <type>unsigned</type>
      <name>size</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a3cb3a68755dc1662ae6f82d9d8c0a815</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>union image_filter_FILTER::@3</type>
      <name>filter</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a100928ec8ffed698af4efbd084710b1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_filter_MASK_GRID</type>
      <name>mask</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>a4e6bbeb038c65fee03427fd5827fa997</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_filter_FILTER_FUNCTION</type>
      <name>function</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>a8525198d3c152f3da271bc0e32fe9617</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_filter_MODE</type>
      <name>mode</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a7b2c5d0f2fefbdf01798414000fc4387</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>image_filter_IMG</name>
    <filename>a00004.html</filename>
    <member kind="variable">
      <type>unsigned</type>
      <name>width</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>ac0b6deb570d85ea8e2fa54974b421598</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>height</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>a96a2da8de6bd5ff8884dc8a673b2dd8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_filter_DATA_GRID</type>
      <name>content</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>a677eab141bbe72423b97a2447467428b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>image_reconstruct_PARAMETERS</name>
    <filename>a00005.html</filename>
    <member kind="variable">
      <type>union image_reconstruct_PARAMETERS::@4</type>
      <name>params</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>aff266d5a2030f7e533522cfc2daf8b66</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>gaussian_sigma</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>a44633966cc6ac21aaa00ab1d85eec27e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_reconstruct_NON_MAXIMA_FILTER_TYPE</type>
      <name>non_maxima_type</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>a7443d5bc4568ad67599182f022bcba3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_reconstruct_PREPROCESS_TYPE</type>
      <name>type</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>aedf0c7f993a2910fbe0e0bcf50c1a04b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>size</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>af0fd001e0dab3dbc0cdb957c5df6b60b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_reconstruct_SCALE_METHOD</type>
      <name>scaling</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>aa23534311798ee5587cc24f448f1bca9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>percent_calculator_CALCULATOR</name>
    <filename>a00006.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>min</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>ac08616554fb94f35aa4ef42906c79b6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>max</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>a1ce078b450197ee12c11779350e90c73</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</path>
    <filename>dir_f66e1f8c5e51043fa03bf003979e5940.html</filename>
    <file>dumper.h</file>
    <file>gaussian_filter.h</file>
    <file>haar_transformation.h</file>
    <file>hrirconfig.h</file>
    <file>image_amplifier.h</file>
    <file>image_filter.h</file>
    <file>image_reconstruct.h</file>
    <file>median_filter.h</file>
    <file>non_maxima.h</file>
    <file>percent_calculator.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/include/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/</path>
    <filename>dir_4d47a3359d3b6180483f780da6526630.html</filename>
    <dir>/home/elesd/programing/github/smart_hrir/source/libs/include/hrir/</dir>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/</path>
    <filename>dir_6719ab1f1f7655efc2fa43f7eb574fd1.html</filename>
    <dir>/home/elesd/programing/github/smart_hrir/source/libs/include/</dir>
  </compound>
</tagfile>
