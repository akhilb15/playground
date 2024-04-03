mod isa;
use log::{info, error};

fn main() {
    std::env::set_var("RUST_LOG", "info");
    env_logger::init();

    // let inst = isa::Instruction::parse("lw r1 r2 r3").unwrap();
    let inst = match isa::Instruction::parse("sub r1 r2 r3") {
        Ok(inst) => inst,
        Err(e) => {
            error!("{}", e);
            return;
        }
    };

    // log::info!("Instruction: {:?}", inst);
    info!("\n{:#?}", inst);
}
