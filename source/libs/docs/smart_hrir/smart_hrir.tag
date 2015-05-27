<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>hrir_ai.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/smart_hrir/</path>
    <filename>a00004</filename>
    <class kind="struct">hrir_ai_ELEMENT</class>
    <member kind="function">
      <type>ai_evol_STATE</type>
      <name>hrir_ai_create_init_state</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>a9f1b69c513955afd2b4598424e9fe0d5</anchor>
      <arglist>(const image_filter_IMG *original_image, unsigned keep_counter, unsigned iteration_per_level, unsigned redundancy)</arglist>
    </member>
    <member kind="function">
      <type>ai_evol_STATE</type>
      <name>hrir_ai_iterate</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>a58cf4d2cd73bd42bcfe5798aaa6c9956</anchor>
      <arglist>(const ai_evol_STATE *phase)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>hrir_mutations.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/smart_hrir/</path>
    <filename>a00005</filename>
    <member kind="function">
      <type>void</type>
      <name>hrir_mutations_set_parameters</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>ac26fc6e9ac49a6a0a69537b0b0d0ae82</anchor>
      <arglist>(unsigned element_to_compare, double gaussian_inc_step, double gaussian_dec_step)</arglist>
    </member>
    <member kind="function">
      <type>list_LIST</type>
      <name>hrir_mutations_gaussian_avg</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a0626d7e1b29015e79d2a1c53043a32ff</anchor>
      <arglist>(priority_queue_QUEUE *population, unsigned level)</arglist>
    </member>
    <member kind="function">
      <type>list_LIST</type>
      <name>hrir_mutations_gaussian_max</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>ab596bbc8fae02639cd5a46322015f66b</anchor>
      <arglist>(priority_queue_QUEUE *population, unsigned level)</arglist>
    </member>
    <member kind="function">
      <type>list_LIST</type>
      <name>hrir_mutations_gaussian_min</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a1127830c419620d7078e6fdf910d48bb</anchor>
      <arglist>(priority_queue_QUEUE *population, unsigned level)</arglist>
    </member>
    <member kind="function">
      <type>list_LIST</type>
      <name>hrir_mutations_gaussian_inc</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a3310c1cb3a9094f50d1a0f5091cc8253</anchor>
      <arglist>(priority_queue_QUEUE *population, unsigned level)</arglist>
    </member>
    <member kind="function">
      <type>list_LIST</type>
      <name>hrir_mutations_gaussian_dec</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>afccdc11049cb6ca8d828f0071716c878</anchor>
      <arglist>(priority_queue_QUEUE *population, unsigned level)</arglist>
    </member>
    <member kind="function">
      <type>list_LIST</type>
      <name>hrir_mutations_filter_size_inc</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>adcc751e22e744f364f6641e17e3649ab</anchor>
      <arglist>(priority_queue_QUEUE *population, unsigned level)</arglist>
    </member>
    <member kind="function">
      <type>list_LIST</type>
      <name>hrir_mutations_filter_size_dec</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a2634837fb63928dae2f05626e8176a68</anchor>
      <arglist>(priority_queue_QUEUE *population, unsigned level)</arglist>
    </member>
    <member kind="function">
      <type>list_LIST</type>
      <name>hrir_mutations_random_scale</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a456498bd6ef84e84e59fcdfc785a5a94</anchor>
      <arglist>(priority_queue_QUEUE *population, unsigned level)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>smart_hrir.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/smart_hrir/</path>
    <filename>a00006</filename>
    <class kind="struct">smart_hrir_SETTINGS</class>
    <member kind="function">
      <type>image_filter_IMG</type>
      <name>smart_hrir_start_algorithm</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>a65e756585dabd3f6479eab5e6d0b8731</anchor>
      <arglist>(const image_filter_IMG *input, smart_hrir_SETTINGS *settings, unsigned *reached_iteration, int *reached_rank)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>hrir_ai_ELEMENT</name>
    <filename>a00001.html</filename>
    <member kind="variable">
      <type>const image_filter_IMG *</type>
      <name>original_image</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>ad0c0f1a46bf293fe30592060db7524d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>image_reconstruct_PARAMETERS</type>
      <name>param</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a2a1fa3a3c0603cdb8f577b070f7b6432</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>smart_hrir_SETTINGS</name>
    <filename>a00002.html</filename>
    <member kind="variable">
      <type>unsigned</type>
      <name>keep_counter</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a714475150bd7fe12b306d68785f67141</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>redundancy</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>ab061b89916ebae7f98218891bfa2f436</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>iteration_limit</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a6cb490509e72b23c2327e4c613f317e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>iteration_per_level</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a5733558db24a20e91e237bc34eefa0dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>target_rank</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a7fe041024e3b80d4432497f6be9c7b8f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/include/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/</path>
    <filename>dir_4d47a3359d3b6180483f780da6526630.html</filename>
    <dir>/home/elesd/programing/github/smart_hrir/source/libs/include/smart_hrir/</dir>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/</path>
    <filename>dir_6719ab1f1f7655efc2fa43f7eb574fd1.html</filename>
    <dir>/home/elesd/programing/github/smart_hrir/source/libs/include/</dir>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/include/smart_hrir/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/smart_hrir/</path>
    <filename>dir_693cf0646374ed877716503f7a6886f0.html</filename>
    <file>compile_uti.h</file>
    <file>hrir_ai.h</file>
    <file>hrir_mutations.h</file>
    <file>smart_hrir.h</file>
    <file>smart_hrirconfig.h</file>
  </compound>
</tagfile>
