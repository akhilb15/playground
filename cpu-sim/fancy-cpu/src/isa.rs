/// defines a super basic instruction set architecture

/// Opcodes for instructions
#[derive(PartialEq, Debug)]
pub enum OP {
    /// add dest, src1, src2 - addition
    ADD,
    /// sub dest, src1, src2 - subtraction
    SUB,
    /// mul dest, src1, src2 - multiplication
    MUL,
    /// div dest, src1, src2 - division
    DIV,
    /// addf dest, src1, src2 - floating point add
    ADDF,
    /// subf dest, src1, src2 - floating point sub
    SUBF,
    /// mulf dest, src1, src2 - floating point mul
    MULF,
    /// divf dest, src1, src2 - floating point div
    DIVF,
    /// lb dest, src, offset - load byte (src1 = src, src2 = offset)
    LB,
    /// lw dest, src, offset - load word (src1 = src, src2 = offset)
    LW,
    /// sb src, dest, offset - store byte (src1 = src, src2 = offset)
    SB,
    /// sw src, dest, offset - store word (src1 = src, src2 = offset)
    SW,
}

/// Register (8 registers guaranteed by the ISA - r0 to r7)
#[derive(Debug)]
pub enum ArchRegister {
    R0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
}

/// Source - Either a register or an immediate value
#[derive(Debug)]
pub enum Source {
    Register(ArchRegister),
    Immediate(i32),
}

/// Instruction struct
#[derive(Debug)]
pub struct Instruction {
    opcode: OP,
    dest: ArchRegister,
    src1: Source,
    src2: Source,
}

impl Instruction {
    /// Parse a raw instruction string into an Instruction struct
    pub fn parse(raw_inst: &str) -> Result<Instruction, &'static str> {
        // convert to lowercase
        let raw_inst = raw_inst.to_lowercase();

        // split into tokens
        let tokens: Vec<&str> = raw_inst.split_whitespace().collect();
        if tokens.len() != 4 {
            return Err("Invalid instruction format");
        }

        // Parse opcode
        let opcode = Self::str_to_opcode(tokens[0])?;

        // Parse destination register
        let dest = Self::str_to_reg(if opcode == OP::SB || opcode == OP::SW {
            // dest is the second argument for store instructions
            tokens[2]
        } else {
            tokens[1]
        })?;

        // Parse source 1
        let src1 = Self::str_to_src(if opcode == OP::SB || opcode == OP::SW {
            // src is the first argument for store instructions
            tokens[1]
        } else {
            tokens[2]
        })?;

        // Parse source 2
        let src2 = Self::str_to_src(tokens[3])?;
        if opcode == OP::LB || opcode == OP::LW || opcode == OP::SB || opcode == OP::SW {
            // src2 is an offset for load/store instructions and therefore must be an immediate
            if let Source::Register(_) = src2 {
                return Err("Offset must be an immediate value");
            }
        }

        Ok(Instruction {
            opcode,
            dest,
            src1,
            src2,
        })
    }

    /// Helper function to convert a string to an opcode (OP enum)
    fn str_to_opcode(opcode_str: &str) -> Result<OP, &'static str> {
        match opcode_str {
            "add" => Ok(OP::ADD),
            "sub" => Ok(OP::SUB),
            "mul" => Ok(OP::MUL),
            "div" => Ok(OP::DIV),
            "addf" => Ok(OP::ADDF),
            "subf" => Ok(OP::SUBF),
            "mulf" => Ok(OP::MULF),
            "divf" => Ok(OP::DIVF),
            "lb" => Ok(OP::LB),
            "lw" => Ok(OP::LW),
            "sb" => Ok(OP::SB),
            "sw" => Ok(OP::SW),
            _ => Err("Invalid opcode"),
        }
    }

    /// Helper function to convert a string to a register (ArchRegister enum)
    fn str_to_reg(reg_str: &str) -> Result<ArchRegister, &'static str> {
        match reg_str {
            "r0" => Ok(ArchRegister::R0),
            "r1" => Ok(ArchRegister::R1),
            "r2" => Ok(ArchRegister::R2),
            "r3" => Ok(ArchRegister::R3),
            "r4" => Ok(ArchRegister::R4),
            "r5" => Ok(ArchRegister::R5),
            "r6" => Ok(ArchRegister::R6),
            "r7" => Ok(ArchRegister::R7),
            _ => Err("Invalid register"),
        }
    }

    /// Helper function to convert a string to a source (Source enum)
    fn str_to_src(src_str: &str) -> Result<Source, &'static str> {
        if src_str.starts_with("r") {
            return Ok(Source::Register(Self::str_to_reg(src_str)?));
        };
        match src_str.parse::<i32>() {
            Ok(imm) => Ok(Source::Immediate(imm)),
            Err(_) => Err("Invalid source value"),
        }
    }
}
