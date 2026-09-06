use std::{error::Error, ffi::{CStr, CString, NulError, c_char}};

unsafe extern "C" {
    fn hello(name: *const c_char);
    fn recieve() -> *mut c_char;
    fn free_c_char(ptr: *mut c_char);
}

fn fetch_c_string() -> Result<Option<String>, std::str::Utf8Error>{
    unsafe {
        let ptr = recieve();
        if ptr.is_null() {
            return Ok(None);
        }

        let c_string = CStr::from_ptr(ptr);
        let msg = c_string.to_str()?.to_string();
        free_c_char(ptr);
        Ok(Some(msg))
    }
}

fn string_to_hello(msg: String) -> Result<(), NulError>{
    unsafe {
        let c_string = CString::new(msg)?;
        hello(c_string.as_ptr());
    }
    Ok(())
}

fn main() -> Result<(), Box<dyn Error>> {
    if let Some(name) = fetch_c_string()? {
        string_to_hello(name)?;
    }
    
    Ok(())
}