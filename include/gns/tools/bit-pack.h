

/*




union Pack {
  BitPack<64, 0, 17> is_small;
  BitFlag<64, 3>


}

*/
template<unsigned offset>
  struct BitFlag {
    unsigned storage;

    operator = (bool value) {
      // use builtin bit operators
    }

    operator bool() {
      return false;
    }
  };


union MyFlags {
  BitFlag<1> is_readable;

};
