<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>ai_evol.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/ai_evol/</path>
    <filename>a00008</filename>
    <includes id="a00010" name="list.h" local="yes" imported="no">list.h</includes>
    <includes id="a00011" name="priority_queue.h" local="yes" imported="no">priority_queue.h</includes>
    <class kind="struct">ai_evol_ELEMENT</class>
    <class kind="struct">ai_evol_STATE</class>
    <class kind="struct">ai_evol_MUTATION_ELEMENT</class>
    <member kind="typedef">
      <type>int</type>
      <name>ai_evol_MUTATION_METHOD_ID</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>a718dd70dd5597e1668aeeb7cd49fed03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>ai_evol_DESTROY_FUNC</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>a6710253499441c289fb8751c83221e38</anchor>
      <arglist>)(void *element)</arglist>
    </member>
    <member kind="typedef">
      <type>int(*</type>
      <name>ai_evol_RANK_FUNCTION</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>a40f90c3ffcebe63f84cf844eea9167c5</anchor>
      <arglist>)(const ai_evol_ELEMENT *element)</arglist>
    </member>
    <member kind="typedef">
      <type>list_LIST(*</type>
      <name>ai_evol_MUTATION</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>a396a21836c00e192def7ee47518bd001</anchor>
      <arglist>)(priority_queue_QUEUE *population, unsigned level)</arglist>
    </member>
    <member kind="function">
      <type>ai_evol_STATE</type>
      <name>ai_evol_create_state</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>a61910738e890b3251c61720e54b6d18c</anchor>
      <arglist>(list_LIST *mutations, priority_queue_QUEUE *population, unsigned keep_counter, unsigned iteration_per_level, ai_evol_RANK_FUNCTION rank_function, ai_evol_DESTROY_FUNC destroy_func)</arglist>
    </member>
    <member kind="function">
      <type>ai_evol_STATE</type>
      <name>ai_evol_iterate</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>a97a06b871a13fd905db646fe0b696e0a</anchor>
      <arglist>(const ai_evol_STATE *state)</arglist>
    </member>
    <member kind="function">
      <type>ai_evol_STATE</type>
      <name>ai_evol_start</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>ab85b84d8921124d6e274dc719a3f79e5</anchor>
      <arglist>(const ai_evol_STATE *start_phase, const unsigned max_iteration, const int target_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ai_evol_destroy_state</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>ac058af5bcdd4f88db91b9b1c2ee08d91</anchor>
      <arglist>(ai_evol_STATE *state)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>list.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/ai_evol/</path>
    <filename>a00010</filename>
    <class kind="struct">list_NODE</class>
    <class kind="struct">list_LIST</class>
    <member kind="typedef">
      <type>void(*</type>
      <name>list_DESTROY</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>af9f798ca7814dd1b5ef32b7ecfa7462f</anchor>
      <arglist>)(void *element)</arglist>
    </member>
    <member kind="typedef">
      <type>void *(*</type>
      <name>list_COPY</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>a17ecf184324f5152136d35a721def4b3</anchor>
      <arglist>)(void *dest, const void *element, size_t size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>list_init_list</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>a1d2b26917d529007b957a4643c2cefa4</anchor>
      <arglist>(list_LIST *list, unsigned element_size, list_DESTROY destroy_func, list_COPY copy_func)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>list_init_like</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>a699a1a35f9054c6dc82ce9ee1845843f</anchor>
      <arglist>(list_LIST *list, const list_LIST *other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>list_add_element</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>ac30216cf9b9cdf221aa68f1e2f819d9a</anchor>
      <arglist>(list_LIST *list, const void *element)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>list_size</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>ad45f8ded6762e1de3627829064d9b5e9</anchor>
      <arglist>(const list_LIST *list)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>list_element_size</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>aa55f63880ae1e6ea175c26ed2e6e2da2</anchor>
      <arglist>(const list_LIST *list)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>list_is_empty</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>a9cbeca339af8257f88a466490d02b818</anchor>
      <arglist>(const list_LIST *list)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>list_destroy</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>a8a7dff7af74ccfabc9997d1505e1cb3a</anchor>
      <arglist>(list_LIST *list)</arglist>
    </member>
    <member kind="function">
      <type>list_LIST</type>
      <name>list_copy</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>ab993127d4cd88ea8e379c4448e33dd07</anchor>
      <arglist>(const list_LIST *list)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>list_concat_list</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>aed56e847043db6a0171561029b2d2b1e</anchor>
      <arglist>(list_LIST *dest, const list_LIST *source)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>list_revert</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>a02924a0a3efce2aa3a6b6f90d788e6f4</anchor>
      <arglist>(list_LIST *list)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>priority_queue.h</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/ai_evol/</path>
    <filename>a00011</filename>
    <includes id="a00010" name="list.h" local="yes" imported="no">list.h</includes>
    <class kind="struct">priority_queue_ELEMENT</class>
    <class kind="struct">priority_queue_QUEUE</class>
    <member kind="typedef">
      <type>void(*</type>
      <name>priority_queue_DESTROY</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a8b0749461227267e0856a15ce59854c1</anchor>
      <arglist>)(void *element)</arglist>
    </member>
    <member kind="typedef">
      <type>void *(*</type>
      <name>priority_queue_COPY</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a8be2278e923a91d0166c68a26e438ee0</anchor>
      <arglist>)(void *dest, const void *element, size_t size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>priority_queue_init</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a95235adc9e596748082c66067fae13dc</anchor>
      <arglist>(priority_queue_QUEUE *queue, const unsigned capacity, const unsigned element_size, priority_queue_DESTROY destroy_func, priority_queue_COPY clone_func)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>priority_queue_init_like</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>ab66c88738d726c25c13b70d983d59395</anchor>
      <arglist>(priority_queue_QUEUE *queue, const priority_queue_QUEUE *other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>priority_queue_insert</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a072c6297756a780f0bdb180669f7e675</anchor>
      <arglist>(priority_queue_QUEUE *queue, const void *element, const int rank)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>priority_queue_pop</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>afdd086076bc9e624185b0bce2562db59</anchor>
      <arglist>(priority_queue_QUEUE *queue)</arglist>
    </member>
    <member kind="function">
      <type>priority_queue_ELEMENT</type>
      <name>priority_queue_first</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>af21869cc07d5231e36eb36a338569948</anchor>
      <arglist>(const priority_queue_QUEUE *queue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>priority_queue_destroy</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>af517dcd382eeb2228104ba92d5064c8e</anchor>
      <arglist>(priority_queue_QUEUE *queue)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>priority_queue_capacity</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a1472e39366d3b49bb0e04158791786e4</anchor>
      <arglist>(const priority_queue_QUEUE *queue)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>priority_queue_current_size</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a3c7adec21393e53de36fc762d3e7e205</anchor>
      <arglist>(const priority_queue_QUEUE *queue)</arglist>
    </member>
    <member kind="function">
      <type>priority_queue_QUEUE</type>
      <name>priority_queue_copy</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a0329ab35ba1e693d907411671560da63</anchor>
      <arglist>(const priority_queue_QUEUE *queue)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>priority_queue_element_size</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>aa5c2bd8a1c7079c6181d78dd72369051</anchor>
      <arglist>(const priority_queue_QUEUE *queue)</arglist>
    </member>
    <member kind="function">
      <type>list_LIST</type>
      <name>priority_queue_to_list</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a24c1dace7ca91d56903ed656c57fddfc</anchor>
      <arglist>(const priority_queue_QUEUE *queue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>priority_queue_pop_back</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a15f272d0534958950428a5fa2ababb1a</anchor>
      <arglist>(priority_queue_QUEUE *queue, unsigned num_of_elements)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ai_evol_ELEMENT</name>
    <filename>a00001.html</filename>
    <member kind="variable">
      <type>void *</type>
      <name>element</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a35a0ba554bf0676ec76c481e1468d835</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>rank</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a0ccdc51cab1f06849e6518518f1888e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ai_evol_MUTATION_METHOD_ID</type>
      <name>method_id</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a5c392b9ad7400ff3f96c1b6105a82fce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>creation_phase</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a10b5e6a4ed8bd4aea40732c57e3199dc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ai_evol_MUTATION_ELEMENT</name>
    <filename>a00002.html</filename>
    <member kind="variable">
      <type>ai_evol_MUTATION</type>
      <name>mutation</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a779a0a1edc16cb1709054860efd5b6a5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ai_evol_STATE</name>
    <filename>a00003.html</filename>
    <member kind="variable">
      <type>list_LIST</type>
      <name>mutations</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a1ecc1cb59a98ecb473aaa3f9bece314c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>priority_queue_QUEUE</type>
      <name>population</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a729b9f6da125fae3a756808aa6800b12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>keep_counter</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a5583418f98233aa7dc9ce809fc68373f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>phase_counter</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>aebb7070e519b1dfc35290d56844f52a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>iteration_per_level</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a09b8e0c8752408132713a22b60f654e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ai_evol_RANK_FUNCTION</type>
      <name>rank_function</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>aaa7bfad69e416dc6acb8b7fb1e9689ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ai_evol_DESTROY_FUNC</type>
      <name>destroy_func</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a910eede8e95d587194d5e389f7ea0589</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>list_LIST</name>
    <filename>a00004.html</filename>
    <member kind="variable">
      <type>struct list_PRIVATE *</type>
      <name>_private</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>a20752f4888859e0baf612ed6e3c2e130</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct list_NODE *</type>
      <name>first_element</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>aa33724826fc0a1c8b8b27b090156a1e1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>list_NODE</name>
    <filename>a00005.html</filename>
    <member kind="variable">
      <type>void *</type>
      <name>element</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a1141f4bdc9d2c161c74369e806bc7aa4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct list_NODE *</type>
      <name>next</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a76afef1241a7a495df545780c6940854</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>priority_queue_ELEMENT</name>
    <filename>a00006.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>rank</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>a470b27f9697e0f910ae956d26d71f924</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void *</type>
      <name>element</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>a1360ad1d3b5d68be281eed755375a3f8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>priority_queue_QUEUE</name>
    <filename>a00007.html</filename>
    <member kind="variable">
      <type>struct priority_queue_PRIVATE *</type>
      <name>_private</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>a334f4d98ae44012a12e2209cbf5b39fe</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/include/ai_evol/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/ai_evol/</path>
    <filename>dir_d95a0690fba18004e6f75694225ce7da.html</filename>
    <file>ai_evol.h</file>
    <file>ai_evol_config.h</file>
    <file>list.h</file>
    <file>priority_queue.h</file>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/include/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/include/</path>
    <filename>dir_4d47a3359d3b6180483f780da6526630.html</filename>
    <dir>/home/elesd/programing/github/smart_hrir/source/libs/include/ai_evol/</dir>
  </compound>
  <compound kind="dir">
    <name>/home/elesd/programing/github/smart_hrir/source/libs/</name>
    <path>/home/elesd/programing/github/smart_hrir/source/libs/</path>
    <filename>dir_6719ab1f1f7655efc2fa43f7eb574fd1.html</filename>
    <dir>/home/elesd/programing/github/smart_hrir/source/libs/include/</dir>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>AI Evolution algorithm</title>
    <filename>index</filename>
    <docanchor file="index">intro</docanchor>
    <docanchor file="index">basic_things</docanchor>
  </compound>
</tagfile>
