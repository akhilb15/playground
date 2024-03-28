mod isa;
use log::info;

fn main() {
    std::env::set_var("RUST_LOG", "info");
    env_logger::init();

    let inst = isa::Instruction::parse("sub r1 p2 r3").unwrap();
    // log::info!("Instruction: {:?}", inst);
    info!("\n{:#?}", inst);
}
